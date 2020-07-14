# 1. websocket

- [1. websocket](#1-websocket)
  - [1.1. 简介](#11-简介)
  - [1.2. 如何建立连接](#12-如何建立连接)
    - [1.2.1. 客户端：申请协议升级](#121-客户端申请协议升级)
    - [1.2.2. 服务端：响应协议升级](#122-服务端响应协议升级)
    - [1.2.3. `Sec-WebSocket-Key/Accept`的作用](#123-sec-websocket-keyaccept的作用)
  - [1.3. 数据帧格式](#13-数据帧格式)
    - [1.3.1. 数据帧格式概览](#131-数据帧格式概览)
    - [1.3.2. 数据帧格式详解](#132-数据帧格式详解)
    - [1.3.3. 数据掩码算法及作用](#133-数据掩码算法及作用)
  - [1.4. 数据传递](#14-数据传递)
  - [1.5. 连接保持+心跳](#15-连接保持心跳)
  - [1.6. 参考资料](#16-参考资料)

## 1.1. 简介

&emsp;&emsp;WebSocket的出现，使得浏览器具备了实时双向通信的能力。本文由浅入深，介绍了WebSocket如何建立连接、交换数据的细节，以及数据帧的格式。此外，还简要介绍了针对WebSocket的安全攻击，以及协议是如何抵御类似攻击的。

&emsp;&emsp;HTML5开始提供的一种浏览器与服务器进行全双工通讯的网络技术，属于应用层协议。它基于TCP传输协议，并复用HTTP的握手通道。

- 对大部分web开发者来说，上面这段描述有点枯燥，其实只要记住几点：
  - WebSocket可以在浏览器里使用
  - 支持双向通信
  - 使用很简单
  
- 优点
  - 支持双向通信，实时性更强。
  - 更好的二进制支持。
  - 较少的控制开销。连接创建后，ws客户端、服务端进行数据交换时，协议控制的数据包头部较小。在不包含头部的情况下，服务端到客户端的包头只有2~10字节（取决于数据包长度），客户端到服务端的的话，需要加上额外的4字节的掩码。而HTTP协议每次通信都需要携带完整的头部。
  - 支持扩展。ws协议定义了扩展，用户可以扩展协议，或者实现自定义的子协议。（比如支持自定义压缩算法等）

&emsp;&emsp;WebSocket协议是独立的基于TCP的协议。他和HTTP的唯一关系是建立连接的握手操作的升级请求是基于HTTP服务器的。标准是rfc6455,大概有70多页。
&emsp;&emsp;WebSocket默认使用80端口进行连接，而基于TLS（RFC2818）的WebSocket连接是基于443端口的。

## 1.2. 如何建立连接

&emsp;&emsp;WebSocket复用了HTTP的握手通道。具体指的是，客户端通过HTTP请求与WebSocket服务端协商升级协议。协议升级完成后，后续的数据交换则遵照WebSocket的协议。

### 1.2.1. 客户端：申请协议升级

&emsp;&emsp;首先，客户端发起协议升级请求。可以看到，采用的是标准的HTTP报文格式，且只支持GET方法。

```html
GET / HTTP/1.1
Host: localhost:8080
Origin: http://127.0.0.1:3000
Connection: Upgrade
Upgrade: websocket
Sec-WebSocket-Version: 13
Sec-WebSocket-Key: w4v7O6xFTi36lq3RNcgctw==
```

重点请求首部意义如下：

`Connection`: Upgrade：表示要升级协议
`Upgrade`: websocket：表示要升级到websocket协议。
`Sec-WebSocket-Version`: 13：表示websocket的版本。如果服务端不支持该版本，需要返回一个`Sec-WebSocket-Versionheader`，里面包含服务端支持的版本号。
`Sec-WebSocket-Key`：与后面服务端响应首部的`Sec-WebSocket-Accept`是配套的，提供基本的防护，比如恶意的连接，或者无意的连接。

`注意，上面请求省略了部分非重点请求首部。由于是标准的HTTP请求，类似Host、Origin、Cookie等请求首部会照常发送。在握手阶段，可以通过相关请求首部进行 安全限制、权限校验等。`

### 1.2.2. 服务端：响应协议升级

&emsp;&emsp;服务端返回内容如下，状态代码101表示协议切换。到此完成协议升级，后续的数据交互都按照新的协议来。

```html
HTTP/1.1 101 Switching Protocols
Connection:Upgrade
Upgrade: websocket
Sec-WebSocket-Accept: Oy4NRAQ13jhfONC7bP8dTKb4PTU=
```

`备注：每个header都以\r\n结尾，并且最后一行加上一个额外的空行\r\n。此外，服务端回应的HTTP状态码只能在握手阶段使用。过了握手阶段后，就只能采用特定的错误码。`

Sec-WebSocket-Accept根据客户端请求首部的Sec-WebSocket-Key计算出来。

- 计算公式为
  - 将Sec-WebSocket-Key跟258EAFA5-E914-47DA-95CA-C5AB0DC85B11拼接。
  - 通过SHA1计算出摘要，并转成base64字符串。
  - 伪代码如下：toBase64( sha1( Sec-WebSocket-Key + 258EAFA5-E914-47DA-95CA-C5AB0DC85B11 )  )

```JS
const crypto = require('crypto');
const magic = '258EAFA5-E914-47DA-95CA-C5AB0DC85B11';
const secWebSocketKey = 'w4v7O6xFTi36lq3RNcgctw==';

let secWebSocketAccept = crypto.createHash('sha1')
    .update(secWebSocketKey + magic)
    .digest('base64');

console.log(secWebSocketAccept);
// Oy4NRAQ13jhfONC7bP8dTKb4PTU=
```

### 1.2.3. `Sec-WebSocket-Key/Accept`的作用

`Sec-WebSocket-Key/Sec-WebSocket-Accept`在主要作用在于提供基础的防护，减少恶意连接、意外连接。

作用大致归纳如下：

1. 避免服务端收到非法的websocket连接（比如http客户端不小心请求连接websocket服务，此时服务端可以直接拒绝连接）
2. 确保服务端理解websocket连接。因为ws握手阶段采用的是http协议，因此可能ws连接是被一个http服务器处理并返回的，此时客户端可以通过Sec-WebSocket-Key来确保服务端认识ws协议。（并非百分百保险，比如总是存在那么些无聊的http服务器，光处理Sec-WebSocket-Key，但并没有实现ws协议。。。）
3. 用浏览器里发起ajax请求，设置header时，Sec-WebSocket-Key以及其他相关的header是被禁止的。这样可以避免客户端发送ajax请求时，意外请求协议升级（websocket upgrade）
4. 可以防止反向代理（不理解ws协议）返回错误的数据。比如反向代理前后收到两次ws连接的升级请求，反向代理把第一次请求的返回给cache住，然后第二次请求到来时直接把cache住的请求给返回（无意义的返回）。
5. Sec-WebSocket-Key主要目的并不是确保数据的安全性，因为Sec-WebSocket-Key、Sec-WebSocket-Accept的转换计算公式是公开的，而且非常简单，最主要的作用是预防一些常见的意外情况（非故意的）。

`强调：Sec-WebSocket-Key/Sec-WebSocket-Accept 的换算，只能带来基本的保障，但连接是否安全、数据是否安全、客户端/服务端是否合法的 ws客户端、ws服务端，其实并没有实际性的保证。`

## 1.3. 数据帧格式

&emsp;&emsp;客户端、服务端数据的交换，离不开数据帧格式的定义。因此，在实际讲解数据交换之前，我们先来看下WebSocket的数据帧格式。

&emsp;&emsp;WebSocket客户端、服务端通信的最小单位是帧（frame），由1个或多个帧组成一条完整的消息（message）。

- 发送端：将消息切割成多个帧，并发送给服务端；
- 接收端：接收消息帧，并将关联的帧重新组装成完整的消息；
- 详细定义可参考 RFC6455 5.2节 。

### 1.3.1. 数据帧格式概览

下面给出了WebSocket数据帧的统一格式。熟悉TCP/IP协议的同学对这样的图应该不陌生。

1. 从左到右，单位是比特。比如FIN、RSV1各占据1比特，opcode占据4比特。
2. 内容包括了标识、操作代码、掩码、数据、数据长度等。（下一小节会展开）

```txt
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-------+-+-------------+-------------------------------+
 |F|R|R|R| opcode|M| Payload len |    Extended payload length    |
 |I|S|S|S|  (4)  |A|     (7)     |             (16/64)           |
 |N|V|V|V|       |S|             |   (if payload len==126/127)   |
 | |1|2|3|       |K|             |                               |
 +-+-+-+-+-------+-+-------------+ - - - - - - - - - - - - - - - +
 |     Extended payload length continued, if payload len == 127  |
 + - - - - - - - - - - - - - - - +-------------------------------+
 |                               |Masking-key, if MASK set to 1  |
 +-------------------------------+-------------------------------+
 | Masking-key (continued)       |          Payload Data         |
 +-------------------------------- - - - - - - - - - - - - - - - +
 :                     Payload Data continued ...                :
 + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +
 |                     Payload Data continued ...                |
 +---------------------------------------------------------------+
```

### 1.3.2. 数据帧格式详解

&emsp;&emsp;针对前面的格式概览图，这里逐个字段进行讲解，如有不清楚之处，可参考协议规范。

- FIN：1个比特。
  - 如果是1，表示这是消息（message）的最后一个分片（fragment），如果是0，表示不是是消息（message）的最后一个分片（fragment）。
- RSV1, RSV2, RSV3：各占1个比特。
  - 一般情况下全为0。当客户端、服务端协商采用WebSocket扩展时，这三个标志位可以非0，且值的含义由扩展进行定义。
  - 如果出现非零的值，且并没有采用WebSocket扩展，连接出错。
- Opcode: 4个比特。操作代码，
  - Opcode的值决定了应该如何解析后续的数据载荷（data payload）。如果操作代码是不认识的，那么接收端应该断开连接（fail the connection）。
  - 可选的操作代码如下：
    - 0x0：表示一个延续帧。当Opcode为0时，表示本次数据传输采用了数据分片，当前收到的数据帧为其中一个数据分片。
    - 0x1：表示这是一个文本帧（frame）
    - 0x2：表示这是一个二进制帧（frame）
    - 0x3-7：保留的操作代码，用于后续定义的非控制帧。
    - 0x8：表示连接断开。
    - 0x9：表示这是一个ping操作。
    - 0xA：表示这是一个pong操作。
    - 0xB-F：保留的操作代码，用于后续定义的控制帧。
- Mask: 1个比特。
  - 表示是否要对数据载荷进行掩码操作。从客户端向服务端发送数据时，需要对数据进行掩码操作；
  - 从服务端向客户端发送数据时，不需要对数据进行掩码操作。
  - 如果服务端接收到的数据没有进行过掩码操作，服务端需要断开连接。
  - 如果Mask是1，那么在Masking-key中会定义一个掩码键（masking key），并用这个掩码键来对数据载荷进行反掩码。
  - 所有客户端发送到服务端的数据帧，Mask都是1。
- Payload length：数据载荷的长度，单位是字节。为7位，或7+16位，或7+64位。
  - 假设数Payload length === x，如果
  - x为0~125：数据的长度为x字节。
  - x为126：后续2个字节代表一个16位的无符号整数，该无符号整数的值为数据的长度。
  - x为127：后续8个字节代表一个64位的无符号整数，该无符号整数的值为数据的长度。
  - 如果payload length占用了多个字节的话，payload length的二进制表达采用网络序（big endian）。
- Masking-key：0或4字节（32位）
  - 所有从客户端传送到服务端的数据帧，数据载荷都进行了掩码操作，Mask为1，且携带了4字节的Masking-key。如果Mask为0，则没有Masking-key。
  - 载荷数据的长度，不包括mask key的长度。
- Payload data：(x+y) 字节
  - 载荷数据：包括了扩展数据、应用数据。其中，扩展数据x字节，应用数据y字节。
    - 扩展数据：如果没有协商使用扩展的话，扩展数据数据为0字节。所有的扩展都必须声明扩展数据的长度，或者可以如何计算出扩展数据的长度。此外，扩展如何使用必须在握手阶段就协商好。如果扩展数据存在，那么载荷数据长度必须将扩展数据的长度包含在内。
    - 应用数据：任意的应用数据，在扩展数据之后（如果存在扩展数据），占据了数据帧剩余的位置。载荷数据长度 减去 扩展数据长度，就得到应用数据的长度。

- 补充
  - 关闭帧可能包含内容（body）（帧的“应用数据”部分）来表明连接关闭的原因，例如终端的断开，或者是终端收到了一个太大的帧，或者是终端收到了一个不符合预期的格式的内容。如果这个内容存在，内容的前两个字节必须是一个无符号整型（按照网络字节序）来代表在7.4节中定义的状态码。跟在这两个整型字节之后的可以是UTF-8编码的的数据值（原因）
  - 控制帧必须有一个126字节或者更小的负载长度，并且不能被分片。控制帧必须有一个126字节或者更小的负载长度，并且不能被分片（比如：0x8,0x9,0xA,0xB）。

### 1.3.3. 数据掩码算法及作用

&emsp;&emsp;掩码键（Masking-key）是由客户端挑选出来的32位的随机数。掩码操作不会影响数据载荷的长度。掩码、反掩码操作都采用如下算法：

首先，假设：

- original-octet-i：为原始数据的第i字节。
- transformed-octet-i：为转换后的数据的第i字节。
- j：为i mod 4的结果。
- masking-key-octet-j：为mask key第j字节。

算法描述为： original-octet-i 与 masking-key-octet-j 异或后，得到 transformed-octet-i。

```JS
j = i MOD 4
transformed-octet-i = original-octet-i XOR masking-key-octet-j
```

&emsp;&emsp;WebSocket协议中，数据掩码的作用是增强协议的安全性。但数据掩码并不是为了保护数据本身，因为算法本身是公开的，运算也不复杂。除了加密通道本身，似乎没有太多有效的保护通信安全的办法。

&emsp;&emsp;那么为什么还要引入掩码计算呢，除了增加计算机器的运算量外似乎并没有太多的收益（这也是不少同学疑惑的点）。

&emsp;&emsp;答案还是两个字：安全。但并不是为了防止数据泄密，而是为了防止早期版本的协议中存在的代理缓存污染攻击（proxy cache poisoning attacks）等问题。

1、代理缓存污染攻击

在正式描述攻击步骤之前，我们假设有如下参与者：

- 攻击者、攻击者自己控制的服务器（简称“邪恶服务器”）、攻击者伪造的资源（简称“邪恶资源”）
- 受害者、受害者想要访问的资源（简称“正义资源”）
- 受害者实际想要访问的服务器（简称“正义服务器”）
- 中间代理服务器

攻击步骤一：

- 攻击者浏览器 向 邪恶服务器 发起WebSocket连接。根据前文，首先是一个协议升级请求。
- 协议升级请求 实际到达 代理服务器。
- 代理服务器 将协议升级请求转发到 邪恶服务器。
- 邪恶服务器 同意连接，代理服务器 将响应转发给 攻击者。
- 由于 upgrade 的实现上有缺陷，代理服务器 以为之前转发的是普通的HTTP消息。因此，当协议服务器 同意连接，代理服务器 以为本次会话已经结束。

攻击步骤二：

- 攻击者 在之前建立的连接上，通过WebSocket的接口向 邪恶服务器 发送数据，且数据是精心构造的HTTP格式的文本。其中包含了 正义资源 的地址，以及一个伪造的host（指向正义服务器）。（见后面报文）
- 请求到达 代理服务器 。虽然复用了之前的TCP连接，但 代理服务器 以为是新的HTTP请求。
- 代理服务器 向 邪恶服务器 请求 邪恶资源。
- 邪恶服务器 返回 邪恶资源。代理服务器 缓存住 邪恶资源（url是对的，但host是 正义服务器 的地址）。

- 到这里，受害者可以登场了：
- 受害者 通过 代理服务器 访问 正义服务器 的 正义资源。
- 代理服务器 检查该资源的url、host，发现本地有一份缓存（伪造的）。
- 代理服务器 将 邪恶资源 返回给 受害者。
- 受害者 卒。

附：前面提到的精心构造的“HTTP请求报文”。

```http
Client → Server:
POST /path/of/attackers/choice HTTP/1.1 Host: host-of-attackers-choice.com Sec-WebSocket-Key: <connection-key>
Server → Client:
HTTP/1.1 200 OK
Sec-WebSocket-Accept: <connection-key>
```

2、当前解决方案
&emsp;&emsp;最初的提案是对数据进行加密处理。基于安全、效率的考虑，最终采用了折中的方案：对数据载荷进行掩码处理。

&emsp;&emsp;需要注意的是，这里只是限制了浏览器对数据载荷进行掩码处理，但是坏人完全可以实现自己的WebSocket客户端、服务端，不按规则来，攻击可以照常进行。

&emsp;&emsp;但是对浏览器加上这个限制后，可以大大增加攻击的难度，以及攻击的影响范围。如果没有这个限制，只需要在网上放个钓鱼网站骗人去访问，一下子就可以在短时间内展开大范围的攻击。

## 1.4. 数据传递

&emsp;&emsp;一旦WebSocket客户端、服务端建立连接后，后续的操作都是基于数据帧的传递。

&emsp;&emsp;WebSocket根据opcode来区分操作的类型。比如0x8表示断开连接，0x0-0x2表示数据交互。

1、数据分片
&emsp;&emsp;WebSocket的每条消息可能被切分成多个数据帧。当WebSocket的接收方收到一个数据帧时，会根据FIN的值来判断，是否已经收到消息的最后一个数据帧。FIN=1表示当前数据帧为消息的最后一个数据帧，此时接收方已经收到完整的消息，可以对消息进行处理。FIN=0，则接收方还需要继续监听接收其余的数据帧。

&emsp;&emsp;此外，opcode在数据交换的场景下，表示的是数据的类型。0x01表示文本，0x02表示二进制。而0x00比较特殊，表示延续帧（continuation frame），顾名思义，就是完整消息对应的数据帧还没接收完。

2、数据分片例子
&emsp;&emsp;直接看例子更形象些。下面例子来自MDN，可以很好地演示数据的分片。客户端向服务端两次发送消息，服务端收到消息后回应客户端，这里主要看客户端往服务端发送的消息。

```websocket
Client: FIN=1, opcode=0x1, msg="hello"
Server: (process complete message immediately) Hi.
Client: FIN=0, opcode=0x1, msg="and a"
Server: (listening, new message containing text started)
Client: FIN=0, opcode=0x0, msg="happy new"
Server: (listening, payload concatenated to previous message)
Client: FIN=1, opcode=0x0, msg="year!"
Server: (process complete message) Happy new year to you too!
```

- FIN=1, 表示是当前消息的最后一个数据帧。服务端收到当前数据帧后，可以处理消息。opcode=0x1，表示客户端发送的是文本类型。
- FIN=0，opcode=0x1，表示发送的是文本类型，且消息还没发送完成，还有后续的数据帧。
- FIN=0，opcode=0x0，表示消息还没发送完成，还有后续的数据帧，当前的数据帧需要接在上一条数据帧之后。
- FIN=1，opcode=0x0，表示消息已经发送完成，没有后续的数据帧，当前的数据帧需要接在上一条数据帧之后。服务端可以将关联的数据帧组装成完整的消息。

## 1.5. 连接保持+心跳

&emsp;&emsp;WebSocket为了保持客户端、服务端的实时双向通信，需要确保客户端、服务端之间的TCP通道保持连接没有断开。然而，对于长时间没有数据往来的连接，如果依旧长时间保持着，可能会浪费包括的连接资源。

&emsp;&emsp;但不排除有些场景，客户端、服务端虽然长时间没有数据往来，但仍需要保持连接。这个时候，可以采用心跳来实现。

- 发送方->接收方：ping
- 接收方->发送方：pong

ping、pong的操作，对应的是WebSocket的两个控制帧，opcode分别是`0x9`、`0xA`。

举例，WebSocket服务端向客户端发送ping，只需要如下代码（采用ws模块）

`ws.ping('', false, true);`

## 1.6. 参考资料

1. [WebSocket 教程](https://www.ruanyifeng.com/blog/2017/05/websocket.html)
2. [WebSocket协议：5分钟从入门到精通](https://www.cnblogs.com/chyingp/p/websocket-deep-in.html)
3. [官网](http://websocket.org/)
4. [rfc](https://tools.ietf.org/html/rfc6455)
