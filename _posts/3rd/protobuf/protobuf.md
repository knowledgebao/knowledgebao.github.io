m# 1. protobuf3

- [1.1. 简介](#11-简介)
- [1.2. 使用方法](#12-使用方法)
- [1.3. protobuf语法](#13-protobuf语法)
  - [1.3.1. option](#131-option)
  - [1.3.2. message](#132-message)
  - [1.3.3. oneof](#133-oneof)
  - [1.3.4. enum](#134-enum)
  - [1.3.5. 具体type](#135-具体type)
    - [1.3.5.1. map](#1351-map)
    - [1.3.5.2. 数字类型](#1352-数字类型)
    - [1.3.5.3. bool类型](#1353-bool类型)
    - [1.3.5.4. 字符串](#1354-字符串)
    - [1.3.5.5. bytes](#1355-bytes)
    - [1.3.5.6. Any](#1356-any)
    - [1.3.5.7. 其他](#1357-其他)
    - [1.3.5.8. 未知类型](#1358-未知类型)
  - [1.3.6. 其他关键字](#136-其他关键字)
    - [1.3.6.1. syntax](#1361-syntax)
    - [1.3.6.2. package](#1362-package)
    - [1.3.6.3. import](#1363-import)
    - [1.3.6.4. repeated](#1364-repeated)
    - [1.3.6.5. reserved](#1365-reserved)
- [1.4. protobuf2和protobuf3的区别](#14-protobuf2和protobuf3的区别)
- [1.5. 参考资料](#15-参考资料)

## 1.1. 简介

Protocol Buffer (简称Protobuf) 是Google出品的性能优异、跨语言、跨平台的序列化库。

## 1.2. 使用方法

- 使用者定义一个以 .proto 结尾的文件，使用此文件中的结构进行交互。
- 文件内容要满足 protobuf 的语法，.proto 文件可以转化为各种语言，下边是一个简单例子。

```protobuf
syntax = "proto3";
message SearchRequest {
  string query = 1;
  int32 page_number = 2;
  int32 result_per_page = 3;
}
```

- 如何转化为各种语言(假设上边内容文件名叫simple.proto)：
`protoc -I=. -I/usr/local/include -I=$(GOPATH)/src --go_out=. simple.proto`

- -I 是 --proto_path 的缩写，表示从什么地方 import 其它 pb 文件，默认会从当前文件夹下查找
- simple.proto是要处理的pb文件，当然也可以写成 *.proto
- 此命令会转为 golang 使用的结构体。同理支持cpp_out用来生成C++代码，java_out产生Java代码，python_out产生python代码，类似地还有csharp_out、objc_out、ruby_out、php_out等参数。

## 1.3. protobuf语法

protobuf语法用来描述结构信息，然后再转化为各种语言对应的结构。

### 1.3.1. option

类似于预定义，影响对应级别的内容。

Protocol Buffer允许我们在.proto文件中定义一些常用的选项，这样可以指示Protocol Buffer编译器帮助我们生成更为匹配的目标语言代码。Protocol Buffer内置的选项被分为以下三个级别：

- 文件级别，这样的选项将影响当前文件中定义的所有消息和枚举。
- 消息级别，这样的选项仅影响某个消息及其包含的所有字段。
- 字段级别，这样的选项仅仅响应与其相关的字段。

option可以用在proto的scope中，或者message、enum、service的定义中。
可以是Protobuf定义的option，或者自定义的option。

- option的定义格式是"option" optionName "=" constant ";",比如:`option java_package = "com.example.foo";`

一些Protobuf定义的option:

- java_package
- java_multiple_files
- java_outer_classname
- optimize_for
  - (文件选项)：可以设置的值有SPEED、CODE_SIZE 或 LITE_RUNTIME，不同的选项会以下述方式影响C++代码的生成（option optimize_for = CODE_SIZE;）。
    - SPEED (default): protocol buffer编译器将会生成序列化,语法分析和其他高效操作消息类型的方式.这也是最高的优化选项.确定是生成的代码比较大.
    - CODE_SIZE: protocol buffer编译器将会生成最小的类,确定是比SPEED运行要慢
    - LITE_RUNTIME: protocol buffer编译器将会生成只依赖"lite" runtime library (libprotobuf-lite instead of libprotobuf)的类. lite运行时库比整个库更小但是删除了例如descriptors 和 reflection等特性. 这个选项通常用于手机平台的优化.
- cc_enable_arenas
  - (文件选项)：生成的C++代码启用arena allocation内存管理
- objc_class_prefix
- deprecated
  - 弃用的，不建议使用
- default 默认值
- nullable

### 1.3.2. message

- message类似于一个结构体定义，里边是各种类型的field
- message里边可以嵌套message，oneof，enum等

field 格式如下：

`field = [ "repeated" ] type fieldName "=" fieldNumber [ "[" fieldOptions "]" ] ";"`
举例： `repeated double Field1 = 1 [(gogoproto.nullable) = false, packed = true];`

- repeated
    标识此字段可以重复，类似于数组
- type
    数字类型： double、float、int32、int64、uint32、uint64、sint32、sint64: 存储长度可变的浮点数、整数、无符号整数和有符号整数
    存储固定大小的数字类型：fixed32、fixed64、sfixed32、sfixed64: 存储空间固定
    布尔类型: bool
    字符串: string
    bytes: 字节数组
    messageType: 消息类型
    enumType:枚举类型
    map:键值对
- fieldName
    首字母必须是字母类型，然后可以是字母、数字或者下划线_
- fieldNumber/tag
    数字，一个结构里边必须唯一，相当于对应字段的uuid标识,有时候也称为tag。1 ~ 15 只用一个byte进行编码（因此应该留给那些常用的字段），16 ~ 2047 用两个byte进行编码，最大支持到 536870911，但是中间有一段（19000~19999）是protobuf内部使用的；
- fieldOptions
    类似于私有结构,比如 golang 的 tag 就在这里定义

### 1.3.3. oneof

- oneof类似于message，组织一组数据，数据格式复合field格式。
- oneof关键字用于声明一组字段中，必须要有一个字段被赋值；
- 通常比如我们在登陆的时候，可以用手机号、邮箱和用户名登陆，这种时候就可以使用oneof来定义；
- 当我们对oneof其中一个字段赋值时，其他字段的值将会被清空；所以只有最后一次赋值是有效的；
- oneof字段不能同时使用repeated修饰。
- 如果使用C++要防止内存泄露，即后面的set操作会覆盖之前的set操作，导致前面设置的字段对象发生析构，要注意字段对象的指针操作
- 如果使用C++的Swap()方法交换两条oneof消息，两条消息都不会保存之前的字段

```protobuf
message SampleMessage {
  oneof test_oneof {
    string name = 4;
    SubMessage sub_message = 9;
  }
}
```

### 1.3.4. enum

- 枚举类型也是常用的一种类型，它限定字段的值只能取某个特定的值，比如星期类型只能取周一到周日七个值。
- 注意枚举类型的定义采用C++ scoping规则，也就是枚举值是枚举类型的兄弟类型，而不是子类型，所以避免在同一个package定义重名的枚举字段。
- 如果设置allow_alias，允许字段编号重复，RUNNING是STARTED的别名。
- 枚举的常量必须是一个32比特的整数，从效率的角度考虑，不推荐采用负数。
- 第一个枚举值必须是0，而且必须定义。
- 你也可以把枚举类型定义到message中
- 对于无法识别的枚举值，不同的语言有不同的处理。对于Go语言来说，因为枚举类型以int32来表示，所以对应的值依然用int32解析出来，只不过没有对应的枚举值而已。这种情况还是会存在的，比如proto有改动，或者代码强行设置了一个未知的枚举值。

```protobuf
message SearchRequest {
  string query = 1;
  int32 page_number = 2;
  int32 result_per_page = 3;
  enum Corpus {
    UNIVERSAL = 0;
    WEB = 1;
    IMAGES = 2;
    LOCAL = 3;
    NEWS = 4;
    PRODUCTS = 5;
    VIDEO = 6;
  }
  Corpus corpus = 4;
}
```

### 1.3.5. 具体type

Protobuf只定义了6种基本编码类型与实际类型匹配，写protobuf文件，使用used for里的type

| Type | Meaning          | Used For                                                 |
| ---- | ---------------- | -------------------------------------------------------- |
| 0    | Varint           | int32, int64, uint32, uint64, sint32, sint64, bool, enum |
| 1    | 64-bit           | fixed64, sfixed64, double                                |
| 2    | Length-delimited | string, bytes, embedded messages, packed repeated fields |
| 3    | Start group      | groups (deprecated)                                      |
| 4    | End group        | groups (deprecated)                                      |
| 5    | 32-bit           | fixed32, sfixed32, float                                 |

#### 1.3.5.1. map

格式： `map<key_type, value_type> map_field = N;` 示例：`map<string, Project> projects = 3;`

- key_type可以是除浮点指针或bytes外的其他基本类型，value_type可以是任意类型
- Map的字段不可以是重复的(repeated)
- 线性顺序和map值的的迭代顺序是未定义的，所以不能期待map的元素是有序的，所有Map类型的数据是无序的；
- maps可以通过key来排序，数值类型的key通过比较数值进行排序
- 线性解析或者合并的时候，如果出现重复的key值，最后一个key将被使用。从文本格式来解析map，如果出现重复key值则解析失败。

#### 1.3.5.2. 数字类型

数字类型： double, float, int32, int64, uint32, uint64, sint32, sint64: 存储长度可变的浮点数、整数、无符号整数和有符号整数
存储固定大小的数字类型：fixed32、fixed64、sfixed32、sfixed64: 存储空间固定

#### 1.3.5.3. bool类型

布尔类型: bool

#### 1.3.5.4. 字符串

字符串: string

#### 1.3.5.5. bytes

bytes: 字节数组

#### 1.3.5.6. Any

- Any字段允许你处理嵌套数据，并不需要它的proto定义。一个Any以bytes呈现序列化的消息，并且包含一个URL作为这个类型的唯一标识和元数据。
- 为了使用Any类型，你需要引入google/protobuf/any.proto。
- 用于底层预定的私有数据

```protobuf
import "google/protobuf/any.proto";
message ErrorStatus {
  string message = 1;
  repeated google.protobuf.Any details = 2;
}
```

Any类型用来替换proto2中的扩展。

#### 1.3.5.7. 其他

messageType: 已定义的message类型
enumType: 已定义的枚举类型

#### 1.3.5.8. 未知类型

proto3最开始对于不能识别的数据就丢弃掉了，但是自3.5 版本后重新引入了unknown未知字段 ，以匹配proto2的行为。

### 1.3.6. 其他关键字

#### 1.3.6.1. syntax

`syntax = "proto3";` 定义版本号，必须文件第一行写

#### 1.3.6.2. package

`package foo.bar;` 定义包

#### 1.3.6.3. import

`import  "foo.bar";` 导入其他包

#### 1.3.6.4. repeated

标识field可以重复，类似于数组

#### 1.3.6.5. reserved

Reserved可以用来指明此message不使用某些字段，也就是忽略这些字段。
可以通过字段编号范围或者字段名称指定保留的字段
声明保留的字段你就不要再定义了，否则编译的时候会出错。

```protobuf
syntax = "proto3";
package abc;
message AllNormalypes {
  reserved 2, 4 to 6;
  reserved "field14", "field11";
  double field1 = 1;
  // float field2 = 2;
  int32 field3 = 3;
  // int64 field4 = 4;
  // uint32 field5 = 5;
  // uint64 field6 = 6;
  sint32 field7 = 7;
  sint64 field8 = 8;
  fixed32 field9 = 9;
  fixed64 field10 = 10;
  // sfixed32 field11 = 11;
  sfixed64 field12 = 12;
  bool field13 = 13;
  // string field14 = 14;
  bytes field15 = 15;
}
```

## 1.4. protobuf2和protobuf3的区别

proto3相较于proto2支持更多语言但在语法上更为简洁。去除了一些复杂的语法和特性，更强调约定而弱化语法。

- 在第一行非空白非注释行，必须写：syntax = "proto3";
- 删​​除原始值字段的 presence 字段逻辑，删除required字段以及删除默认值，所有都默认为optional
- 开始移除unknown关键字，后来3.5有加上了
- 去掉extensions类型，使用Any新标准类型替换。
- 针对未知枚举值的固定语法.
- 增加maps(主要指代码生成支持map)
- 添加一组用于表示时间，动态数据等的标准类型。
- 替换二进制编码的明确JSON编码
- “repeated”字段默认采用 packed 编码；在 proto2 中，需要明确使用 [packed=true] 来为字段指定比较紧凑的 packed 编码方式。
- 语言增加 Go、Ruby、JavaNano 支持；
- 移除了 default 选项；在 proto2 中，可以使用 default 选项为某一字段指定默认值。在 proto3 中，字段的默认值只能根据字段类型由系统决定。也就是说，默认值全部是约定好的，而不再提供指定默认值的语法。在字段被设置为默认值的时候，该字段不会被序列化。这样可以节省空间，提高效率。但这样就无法区分某字段是根本没赋值，还是赋值了默认值。这在 proto3 中问题不大，但在 proto2 中会有问题。比如，在更新协议的时候使用 default 选项为某个字段指定了一个与原来不同的默认值，旧代码获取到的该字段的值会与新代码不一样。另一个重约定而弱语法的例子是 Go 语言里的公共/私有对象。Go 语言约定，首字母大写的为公共对象，否则为私有对象。所以在 Go 语言中是没有 public、private 这样的语法的。
- 枚举类型的第一个字段必须为 0 ；这也是一个约定。
- 移除了对分组的支持；分组的功能完全可以用消息嵌套的方式来实现，并且更清晰。在 proto2 中已经把分组语法标注为『过期』了。这次也算清理垃圾了。
- 旧代码在解析新增字段时，会把不认识的字段丢弃，再序列化后新增的字段就没了；在 proto2 中，旧代码虽然会忽视不认识的新增字段，但并不会将其丢弃，再序列化的时候那些字段会被原样保留。我觉得还是 proto2 的处理方式更好一些。能尽量保持兼容性和扩展能力，或许实现起来也更简单。proto3 现在的处理方式，没有带来明显的好处，但丢掉了部分兼容性和灵活性。
- 移除了对扩展的支持，新增了 Any 类型；Any 类型是用来替代 proto2 中的扩展的。proto3 中新增的 Any 类型有点像 C/C++ 中的 void* ，好理解，使用起来逻辑也更清晰。
- 增加了 JSON 映射特性；

## 1.5. 参考资料

1. [Protobuf 终极教程](https://colobu.com/2019/10/03/protobuf-ultimate-tutorial-in-go/)
2. [Language Guide (proto3)](https://developers.google.com/protocol-buffers/docs/proto3)
3. [区分 Protobuf 中缺失值和默认值](https://zhuanlan.zhihu.com/p/46603988)
