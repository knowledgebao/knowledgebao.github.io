# 1. java和C++的区别

- [1. java和C++的区别](#1-java%e5%92%8cc%e7%9a%84%e5%8c%ba%e5%88%ab)
  - [1.1. 简介](#11-%e7%ae%80%e4%bb%8b)
  - [1.2. 语法](#12-%e8%af%ad%e6%b3%95)
    - [1.2.1. 基础](#121-%e5%9f%ba%e7%a1%80)
      - [1.2.1.1. 类型](#1211-%e7%b1%bb%e5%9e%8b)
      - [1.2.1.2. 流程控制](#1212-%e6%b5%81%e7%a8%8b%e6%8e%a7%e5%88%b6)
      - [1.2.1.3. 数组](#1213-%e6%95%b0%e7%bb%84)
      - [1.2.1.4. 类](#1214-%e7%b1%bb)
      - [1.2.1.5. jar包，模块](#1215-jar%e5%8c%85%e6%a8%a1%e5%9d%97)
      - [1.2.1.6. String](#1216-string)
      - [1.2.1.7. 异常](#1217-%e5%bc%82%e5%b8%b8)
      - [1.2.1.8. 日志](#1218-%e6%97%a5%e5%bf%97)
      - [1.2.1.9. JavaBean](#1219-javabean)
      - [1.2.1.10. enum](#12110-enum)
      - [1.2.1.11. BigInteger/BigDecimal](#12111-bigintegerbigdecimal)
      - [1.2.1.12. 工具类](#12112-%e5%b7%a5%e5%85%b7%e7%b1%bb)
    - [1.2.2. 反射](#122-%e5%8f%8d%e5%b0%84)
    - [1.2.3. 注解](#123-%e6%b3%a8%e8%a7%a3)
    - [1.2.4. 泛型](#124-%e6%b3%9b%e5%9e%8b)
    - [1.2.5. 日期和时间](#125-%e6%97%a5%e6%9c%9f%e5%92%8c%e6%97%b6%e9%97%b4)
      - [1.2.5.1. Data/Calendar/TimeZone](#1251-datacalendartimezone)
      - [1.2.5.2. LocalDateTime/ZonedDateTime/ZoneId/Instant](#1252-localdatetimezoneddatetimezoneidinstant)
      - [1.2.5.3. 新旧API及数据库时间相关](#1253-%e6%96%b0%e6%97%a7api%e5%8f%8a%e6%95%b0%e6%8d%ae%e5%ba%93%e6%97%b6%e9%97%b4%e7%9b%b8%e5%85%b3)
    - [1.2.6. 集合](#126-%e9%9b%86%e5%90%88)
      - [1.2.6.1. List](#1261-list)
      - [1.2.6.2. Map/Properties](#1262-mapproperties)
      - [1.2.6.3. Set](#1263-set)
      - [1.2.6.4. Queue/Deque/PriorityQueue/Stack](#1264-queuedequepriorityqueuestack)
      - [1.2.6.5. Iterator/Collections](#1265-iteratorcollections)
    - [1.2.7. IO](#127-io)
      - [1.2.7.1. File](#1271-file)
      - [1.2.7.2. InputStream/OutputStream](#1272-inputstreamoutputstream)
      - [1.2.7.3. Filter/Decorator](#1273-filterdecorator)
      - [1.2.7.4. Reader/Writer](#1274-readerwriter)
      - [1.2.7.5. ohter](#1275-ohter)
    - [1.2.8. 单元测试](#128-%e5%8d%95%e5%85%83%e6%b5%8b%e8%af%95)
    - [1.2.9. 多线程](#129-%e5%a4%9a%e7%ba%bf%e7%a8%8b)
      - [1.2.9.1. Thread](#1291-thread)
      - [1.2.9.2. 锁](#1292-%e9%94%81)
      - [1.2.9.3. 线程安全集合](#1293-%e7%ba%bf%e7%a8%8b%e5%ae%89%e5%85%a8%e9%9b%86%e5%90%88)
      - [1.2.9.4. 线程池](#1294-%e7%ba%bf%e7%a8%8b%e6%b1%a0)
    - [1.2.10. 正则表达式](#1210-%e6%ad%a3%e5%88%99%e8%a1%a8%e8%be%be%e5%bc%8f)
    - [1.2.11. 加密与安全](#1211-%e5%8a%a0%e5%af%86%e4%b8%8e%e5%ae%89%e5%85%a8)
    - [1.2.12. Maven基础](#1212-maven%e5%9f%ba%e7%a1%80)
    - [1.2.13. 网络编程基础](#1213-%e7%bd%91%e7%bb%9c%e7%bc%96%e7%a8%8b%e5%9f%ba%e7%a1%80)
    - [1.2.14. XML和JSON](#1214-xml%e5%92%8cjson)
  - [1.3. 参考资料](#13-%e5%8f%82%e8%80%83%e8%b5%84%e6%96%99)

## 1.1. 简介

从互联网到企业平台，Java是应用最广泛的编程语言，原因在于：

- Java是基于JVM虚拟机的跨平台语言，一次编写，到处运行；
- Java程序易于编写，而且有内置垃圾收集，不必考虑内存管理；
- Java虚拟机拥有工业级的稳定性和高度优化的性能，且经过了长时期的考验；
- Java拥有最广泛的开源社区支持，各种高质量组件随时可用。
- Java语言常年霸占着三大市场：

互联网和企业应用，这是Java EE的长期优势和市场地位；

- 大数据平台，主要有Hadoop、Spark、Flink等，他们都是Java或Scala（一种运行于JVM的编程语言）开发的；
- Android移动平台。
- 这意味着Java拥有最广泛的就业市场。

## 1.2. 语法

### 1.2.1. 基础

#### 1.2.1.1. 类型

- 类型，java没有无符号类型,无符号整型和有符号整型的转换在Java中就需要借助包装类型的静态方法完成。比如：`Byte.toUnsignedInt(y)`
- 整数类型：byte，short，int，long
- 浮点数类型：float，double
- 字符类型：char
- 布尔类型：boolean

| 基本类型 | 对应的引用类型      |
| -------- | ------------------- |
| byte     | java.lang.Byte      |
| short    | java.lang.Short     |
| int      | java.lang.Integer   |
| long     | java.lang.Long      |
| float    | java.lang.Float     |
| double   | java.lang.Double    |
| char     | java.lang.Character |
| boolean  | java.lang.Boolean   |

- Java核心库提供的包装类型可以把基本类型包装为class；
- 自动装箱和自动拆箱都是在编译期完成的（JDK>=1.5）；
- 装箱和拆箱会影响执行效率，且拆箱时可能发生NullPointerException；
- 包装类型的比较必须使用equals()；
- 整数和浮点数的包装类型都继承自Number；
- 包装类型提供了大量实用方法。Integer.toString(100, 16),Integer.MAX_VALUE...

浮点数除0不报错
NaN表示Not a Number， 0.0 / 0; // NaN
Infinity表示无穷大，1.0 / 0; // Infinity
-Infinity表示负无穷大， -1.0 / 0; // -Infinity

- 基本类型：byte，short，int，long，boolean，float，double，char
- 引用类型：所有class和interface类型
- 引用类型判断内容相等要使用equals()
- 封装方法1：Integer n = new Integer(100);
- 封装方法2：Integer n = Integer.valueOf(100);推介

一个char保存一个Unicode字符
要显示一个字符的Unicode编码，只需将char类型直接赋值给int类型即可
\u#### 表示一个Unicode编码的字符，注意必须是4个数字

var类似于c++中的auto，自动判断类型
java中变量都会被初始化为默认值。false，0，nill

#### 1.2.1.2. 流程控制

- System.out.println()类似于printf
- 从Java 13开始，switch语句升级为表达式，不再需要break，并且允许使用yield返回值。
注意新语法使用->，如果有多条语句，需要用{}括起来。不要写break语句，因为新语法只会执行匹配的语句，没有穿透效应。
使用新的switch语法，不但不需要break，还可以直接返回值。

```java
public static void main(String[] args) {
        String fruit = "apple";
        int opt = switch (fruit) {
            case "apple" -> 1;
            case "pear", "mango" -> 2;
            default -> 0;
        }; // 注意赋值语句要以;结束,opt赋值为1，2或0
        System.out.println("opt = " + opt);
    }
```

- Java也提供了另一种for each循环

```java
    int[] ns = { 1, 4, 9, 16, 25 };
    for (int n : ns) {
        System.out.println(n);
    }
```

#### 1.2.1.3. 数组

1. Arrays.toString()，可以快速打印数组内容
2. .length获取数组的长度，属性非方法
3. 可以直接使用Java标准库提供的Arrays.sort()进行排序；
4. 要打印一个二维数组，可以使用两层嵌套的for循环，或者使用Java标准库的Arrays.deepToString()

```java
int[] intArr;   //定义一个引用变量
intArr = new int[]{3, 4, 5, 6};

String[] strArr;
strArr = new String[]{"apple", "banana", "orange"};

//简化静态初始化
double[] douArr = {3.4, 5.6, 8.9};

int[] price = new int[5];   //price数组中的5个元素在堆中的默认值都是0
price[0] = 345;
price[1] = 400;
```

#### 1.2.1.4. 类

- 类定义中，类变量可以直接赋初值。
- Java使用extends关键字来实现继承
- 在Java中，没有明确写extends的类，编译器会自动加上extends Object。
- super关键字表示父类（超类）。子类引用父类的字段时，可以用super.fieldName
- 为了避免向下转型出错，Java提供了instanceof操作符，可以先判断一个实例究竟是不是某种类型
- Java继承没有public,protect,private,默认都是public继承
- 方法名相同，方法参数相同，但方法返回值不同，在Java程序中，出现这种情况，编译器会报错。
- 加上@Override可以让编译器帮助检查是否进行了正确的覆写。希望进行覆写，但是不小心写错了方法签名，编译器会报错，这是注解的应用。
- 因为所有的class最终都继承自Object，而Object定义了几个重要的方法：
    toString()：把instance输出为String；
    equals()：判断两个instance是否逻辑相等；
    hashCode()：计算一个instance的哈希值。
- final
    如果一个父类不允许子类对它的某个方法进行覆写，可以把该方法标记为final。用final修饰的方法不能被Override
    final修饰的方法可以阻止被覆写；
    final修饰的class可以阻止被继承；
    final修饰的field必须在创建对象时初始化，随后不可修改。
- abstract 抽象类作用于函数的同时必须作用于类
- interface 接口关键字。如果一个抽象类没有字段，所有方法全部都是抽象方法，就可以把该抽象类改写为接口。所谓interface，就是比抽象类还要抽象的纯抽象接口，因为它连字段都不能有。因为接口定义的所有方法默认都是public abstract的，所以这两个修饰符不需要写出来（写不写效果都一样）。
  - 当一个具体的class去实现一个interface时，需要使用implements关键字。在Java中，一个类只能继承自另一个类，不能从多个类继承。但是，一个类可以实现多个interface，例如：`class Student implements Person, Hello`
  - 一个interface可以继承自另一个interface。interface继承自interface使用extends，它相当于扩展了接口的方法。
  - 在接口中，可以定义default方法。例如，把Person接口的run()方法改为default方法：`default void run()`，实现类可以不必覆写default方法。default方法的目的是，当我们需要给接口新增一个方法时，会涉及到修改全部子类。如果新增的是default方法，那么子类就不必全部修改，只需要在需要覆写的地方去覆写新增方法。
  - 因为interface是一个纯抽象类，所以它不能定义实例字段。但是，interface是可以有静态字段的，并且静态字段必须为final类型： `public static final int MALE = 1;`实际上，因为interface的字段只能是public static final类型，所以我们可以把这些修饰符都去掉，上述代码可以简写为：int MALE = 1;
  - 静态方法的访问，`类名.静态字段`来访问静态对象
- 使用package来解决名字冲突
    包可以是多层结构，用.隔开。例如：java.util。
    包没有父子关系。java.util和java.util.zip是不同的包，两者没有任何继承关系。
    没有定义包名的class，它使用的是默认包，非常容易引起名字冲突，因此，不推荐不写包名的做法。
    Java内建的package机制是为了避免class命名冲突；
    JDK的核心类使用java.lang包，编译器会自动导入；
    JDK的其它常用类定义在java.util.*，java.math.*，java.text.*，……；
    通过package ming来为文件添加package，通过import来包含包
- 由于Java支持嵌套类，如果一个类内部还定义了嵌套类，那么，嵌套类拥有访问private的权限
    一个.java文件只能包含一个public类，但可以包含多个非public类。如果有public类，文件名必须和public类的名字相同。
    Java内建的访问权限包括public、protected、private和package权限；

```java
Person p = new Person();
System.out.println(p instanceof Person); // true
System.out.println(p instanceof Student); // false
```

```java
public class Main {
    public static void main(String[] args) {
    }
}

class Person {
    public void run() {}
}

public class Student extends Person {
    @Override // Compile error!
    public void run(String s) {}
}
```

#### 1.2.1.5. jar包，模块

- classpath是JVM用到的一个环境变量，它用来指示JVM如何搜索class。
- jar包相当于目录，可以包含很多.class文件，方便下载和使用；MANIFEST.MF文件可以提供jar包的信息，如Main-Class，这样可以直接运行jar包。
- Java 9引入的模块目的是为了管理依赖；
    使用模块可以按需打包JRE；
    使用模块对类的访问权限有了进一步限制。

#### 1.2.1.6. String

- Java字符串String是不可变对象；
- 字符串操作不改变原字符串内容，而是返回新字符串；
- 常用的字符串操作：提取子串、查找、替换、大小写转换等；
- Java使用Unicode编码表示String和char；
- 转换编码就是将String和byte[]转换，需要指定编码；
- 转换为byte[]时，始终优先考虑UTF-8编码。

- StringBuilder是可变对象，用来高效拼接字符串；
- StringBuilder可以支持链式操作，实现链式操作的关键是返回实例本身；
- StringBuffer是StringBuilder的线程安全版本，现在很少使用。

- 用指定分隔符拼接字符串数组时，使用StringJoiner或者String.join()更方便；
- 用StringJoiner拼接字符串时，还可以额外附加一个“开头”和“结尾”。

多行字符串前面共同的空格会被去掉,如果多行字符串的排版不规则,总是以最短的行首空格为基准。最后"""与字符串同行不会加\n，如果换写"""会加\n

```java
String s = """
        SELECT * FROM
            users
        WHERE id > 100
        ORDER BY name DESC""";
```

#### 1.2.1.7. 异常

- Java使用异常来表示错误，并通过try ... catch捕获异常；
- Java的异常是class，并且从Throwable继承；
- Error是无需捕获的严重错误，Exception是应该捕获的可处理的错误；
- RuntimeException无需强制捕获，非RuntimeException（Checked Exception）需强制捕获，或者用throws声明；
- 从继承关系可知：Throwable是异常体系的根，它继承自Object。Throwable有两个体系：Error和Exception
- Error表示严重的错误，程序对此一般无能为力，例如
  - OutOfMemoryError：内存耗尽
  - NoClassDefFoundError：无法加载某个Class
  - StackOverflowError：栈溢出
- Exception分类如下
Exception
├─ RuntimeException
│  ├─ NullPointerException 对某个null的对象调用方法或字段
│  ├─ IndexOutOfBoundsException 数组索引越界
│  ├─ SecurityException
│  └─ IllegalArgumentException 非法参数
│     └─ NumberFormatException 数值类型的格式错误
├─ IOException
│  ├─ UnsupportedCharsetException
│  ├─ FileNotFoundException 未找到文件
│  └─ SocketException 读取网络失败
├─ ParseException
├─ GeneralSecurityException
├─ SQLException
└─ TimeoutException

- 必须捕获的异常，包括Exception及其子类，但不包括RuntimeException及其子类，这种类型的异常称为Checked Exception。
- 不需要捕获的异常，包括Error及其子类，RuntimeException及其子类。
- 使用try ... catch ... finally时
  - 多个catch语句的匹配顺序非常重要，子类必须放在前面；
  - finally语句保证了有无异常都会执行，它是可选的；
  - 一个catch语句也可以匹配多个非继承关系的异常。`catch (IOException | NumberFormatException e)`
- 调用 printStackTrace()可以打印异常的传播栈，对于调试非常有用；
- 捕获异常并再次抛出新的异常时，应该持有原始异常信息；
- 通常不要在finally中抛出异常。如果在finally中抛出异常，应该原始异常加入到原有异常中。调用方可通过Throwable.getSuppressed()获取所有添加的Suppressed Exception。
- 抛出异常时，尽量复用JDK已定义的异常类型；
- 自定义异常体系时，推荐从RuntimeException派生“根异常”，再派生出业务异常；
- 自定义异常时，应该提供多种构造方法。
- 断言是一种调试方式，断言失败会抛出AssertionError，只能在开发和测试阶段启用断言；要执行assert语句，必须给Java虚拟机传递-enableassertions（可简写为-ea）参数启用断言。可以有选择地对特定地类启用断言，命令行参数是：-ea:com.itranswarp.sample.Main

#### 1.2.1.8. 日志

- Java标准库
  - 提供了java.util.logging来实现日志功能。
  - Logging系统在JVM启动时读取配置文件并完成初始化，一旦开始运行main()方法，就无法修改配置；
  - 配置不太方便，需要在JVM启动时传递参数`-Djava.util.logging.config.file=<config-file-name>`。
  - 级别分7级。SEVERE/WARNING/INFO/CONFIG/FINE/FINER/FINEST
- Commons Logging接口
  - 是使用最广泛的日志模块；Commons Logging的API非常简单；
  - Commons Loggin自动搜索并使用Log4j（Log4j是另一个流行的日志系统），如果没有找到Log4j，再使用JDK Logging。
  - 级别分6级。FATAL/ERROR/WARNING/INFO/DEBUG/TRACE
- Log4j
  - 通过Commons Logging接口实现日志，不需要修改代码即可使用Log4j；
  - 使用Log4j只需要把log4j2.xml和相关jar放入classpath；
  - 只有扩展Log4j时，才需要引用Log4j的接口（例如，将日志加密写入数据库的功能，需要自己开发）。
- SLF4J和Logback
  - 可以取代Commons Logging和Log4j；
  - SLF4J支持python带{}格式的format

#### 1.2.1.9. JavaBean

- JavaBean是一种符合命名规范的class，它通过getter和setter来定义属性；
- 属性是一种通用的叫法，并非Java语法规定；
- 可以利用IDE快速生成getter和setter；
- 使用Introspector.getBeanInfo()可以获取属性列表。

#### 1.2.1.10. enum

- Java使用enum定义枚举类型，它被编译器编译为final class Xxx extends Enum { … }；
- 通过name()获取常量定义的字符串，注意不要使用toString()；
- 通过ordinal()返回常量定义的顺序（无实质意义）；
- 可以为enum编写构造方法、字段和方法
- enum的构造方法要声明为private，字段强烈建议声明为final；
- enum适合用在switch语句中。

#### 1.2.1.11. BigInteger/BigDecimal

- BigInteger用于表示任意大小的整数；
- BigInteger是不变类，并且继承自Number；
- 将BigInteger转换成基本类型时可使用longValueExact()等方法保证结果准确。

- BigDecimal用于表示精确的小数，常用于财务计算；
- 比较BigDecimal的值是否相等，必须使用compareTo()而不能使用equals()。

#### 1.2.1.12. 工具类

- Math：数学计算
- Random：生成伪随机数
- SecureRandom：生成安全的随机数

### 1.2.2. 反射

- JVM为每个加载的class及interface创建了对应的Class实例来保存class及interface的所有信息；
- 获取一个class对应的Class实例后，就可以获取该class的所有信息；
- 通过Class实例获取class信息的方法称为反射（Reflection）；
- JVM总是动态加载class，可以在运行期根据条件来控制加载class。
- 如何获取一个class的Class实例？有三个方法：
  - 方法一：直接通过一个class的静态变量class获取：`Class cls = String.class;`
  - 方法二：如果我们有一个实例变量，可以通过该实例变量提供的getClass()方法获取：`String s = "Hello";Class cls = s.getClass();`
  - 方法三：如果知道一个class的完整类名，可以通过静态方法Class.forName()获取：`Class cls = Class.forName("java.lang.String");`
- 除了int等基本类型外，Java的其他类型全部都是class（包括interface）
- Class的方法：`getName(); getSimpleName(); cls.getPackage().getName(); isInterface(); isEnum(); isArray(); isPrimitive()...`

- Java的反射API提供的Field类封装了字段的所有信息：
- Class-Field
  - 通过Class实例的方法可以获取Field实例
    - Field getField(name)：根据字段名获取某个public的field（包括父类）
    - Field getDeclaredField(name)：根据字段名获取当前类的某个field（不包括父类）
    - Field[] getFields()：获取所有public的field（包括父类）
    - Field[] getDeclaredFields()：获取当前类的所有field（不包括父类）
  - 通过Field实例可以获取字段信息：getName()，getType()，getModifiers()；
  - 通过Field实例可以读取或设置某个对象的字段，如果存在访问限制，要首先调用setAccessible(true)来访问非public字段。
  - 通过反射读写字段是一种非常规方法，它会破坏对象的封装。
  - 一个Field对象包含了一个字段的所有信息：
    - getName()：返回字段名称，例如，"name"；
    - getType()：返回字段类型，也是一个Class实例，例如，String.class；
    - getModifiers()：返回字段的修饰符，它是一个int，不同的bit表示不同的含义。

- Class-Method
  - Java的反射API提供的Method对象封装了方法的所有信息：
  - 通过Class实例的方法可以获取Method实例
    - Method getMethod(name, Class...)：获取某个public的Method（包括父类）
    - Method getDeclaredMethod(name, Class...)：获取当前类的某个Method（不包括父类）
    - Method[] getMethods()：获取所有public的Method（包括父类）
    - Method[] getDeclaredMethods()：获取当前类的所有Method（不包括父类）
  - 通过Method实例可以获取方法信息：getName()，getReturnType()，getParameterTypes()，getModifiers()；
  - 通过Method实例可以调用某个对象的方法：Object invoke(Object instance, Object... parameters)；
  - 通过设置setAccessible(true)来访问非public方法；
  - 通过反射调用方法时，仍然遵循多态原则。
  - 一个Method对象包含一个方法的所有信息：
    - getName()：返回方法名称，例如："getScore"；
    - getReturnType()：返回方法返回值类型，也是一个Class实例，例如：String.class；
    - getParameterTypes()：返回方法的参数类型，是一个Class数组，例如：{String.class, int.class}；
    - getModifiers()：返回方法的修饰符，它是一个int，不同的bit表示不同的含义。

- Class-Constructor
  - 可以通过Class的newInstance() 实例化类。调用Class.newInstance()的局限是，它只能调用该类的public无参数构造方法。如果构造方法带有参数，或者不是public，就无法直接通过Class.newInstance()来调用。需要通过Constructor来构建。
  - Constructor对象封装了构造方法的所有信息；
  - 通过Class实例的方法可以获取Constructor实例
    - getConstructor(Class...)：获取某个public的Constructor；
    - getDeclaredConstructor(Class...)：获取某个Constructor；
    - getConstructors()：获取所有public的Constructor；
    - getDeclaredConstructors()：获取所有Constructor。
  - 通过Constructor实例可以创建一个实例对象：newInstance(Object... parameters)； 通过设置setAccessible(true)来访问非public构造方法。

- 继承关系
  - 通过Class对象可以获取继承关系：
  - Class getSuperclass()：获取父类类型；
  - Class[] getInterfaces()：获取当前类实现的所有接口。
  - 通过Class对象的isAssignableFrom()方法可以判断一个向上转型是否可以实现。
  - 对接口调用getSuperclass()总是返回null，获取接口的父接口要用getInterfaces()

- 动态代理
  - Java标准库提供了动态代理功能，允许在运行期动态创建一个接口的实例；
  - 动态代理是通过Proxy创建代理对象，然后将接口方法“代理”给InvocationHandler完成的。

### 1.2.3. 注解

- 注解（Annotation）是Java语言用于工具处理的标注：
- 注解可以配置参数，没有指定配置的参数使用默认值；
- 如果参数名称是value，且只有一个参数，那么可以省略参数名称。核心参数使用value名称；
- 注解定义后也是一种class，所有的注解都继承自java.lang.annotation.Annotation，因此，读取注解，需要使用反射API。
  
- Java使用@interface定义注解
- 可定义多个参数和默认值，核心参数使用value名称；
- 必须设置@Target来指定 Annotation 可以应用的范围；
  - 类或接口：ElementType.TYPE；
  - 字段：ElementType.FIELD；
  - 方法：ElementType.METHOD；
  - 构造方法：ElementType.CONSTRUCTOR；
  - 方法参数：ElementType.PARAMETER。

- 应当设置@Retention(RetentionPolicy.RUNTIME) 便于运行期读取该Annotation。
  - 仅编译期：RetentionPolicy.SOURCE；SOURCE类型的注解主要由编译器使用，因此我们一般只使用，不编写。
  - 仅class文件：RetentionPolicy.CLASS；CLASS类型的注解主要由底层工具库使用，涉及到class的加载，一般我们很少用到。
  - 运行期：RetentionPolicy.RUNTIME。常用

- 使用@Repeatable这个元注解可以定义Annotation是否可重复。
- 使用@Inherited定义子类是否可继承父类定义的Annotation

- 判断某个注解是否存在于Class、Field、Method或Constructor：
  - Class.isAnnotationPresent(Class)
  - Field.isAnnotationPresent(Class)
  - Method.isAnnotationPresent(Class)
  - Constructor.isAnnotationPresent(Class)

- 使用反射API读取Annotation：
  - Class.getAnnotation(Class)
  - Field.getAnnotation(Class)
  - Method.getAnnotation(Class)
  - Constructor.getAnnotation(Class)
  - Method.getParameterAnnotations()
- 读取方法参数的Annotation就比较麻烦一点，因为方法参数本身可以看成一个数组，而每个参数又可以定义多个注解，所以，一次获取方法参数的所有注解就必须用一个二维数组来表示

- 使用反射API读取Annotation有两种方法。
  - 方法一是先判断Annotation是否存在，如果存在，就直接读取
  - 第二种方法是直接读取Annotation，如果Annotation不存在，将返回null

注解如何使用，完全由程序自己决定。下例我们通过@Range注解，配合check()方法，可以完成Person实例的检查。

```java
//Range.java
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.FIELD)
public @interface Range {
    int min() default 0;
    int max() default 255;
}

//Person.java
public class Person {
    @Range(min=1, max=20)
    public String name;

    @Range(max=10)
    public String city;
}

//Main.java
public class Main {
    public static void main(String[] args) throws Exception {
        Person p1 = new Person("Bob", "Beijing", 20);
        Person p2 = new Person("", "Shanghai", 20);//IllegalArgumentException
        Person p3 = new Person("Alice", "Shanghai", 199);//IllegalArgumentException
        for (Person p : new Person[] { p1, p2, p3 }) {
            try {
                check(p);
                System.out.println("Person " + p + " checked ok.");
            } catch (IllegalArgumentException e) {
                System.out.println("Person " + p + " checked failed: " + e);
            }
        }
    }

    void check(Person person) throws IllegalArgumentException, ReflectiveOperationException {
        // 遍历所有Field:
        for (Field field : person.getClass().getFields()) {
            // 获取Field定义的@Range:
            Range range = field.getAnnotation(Range.class);
            // 如果@Range存在:
            if (range != null) {
                // 获取Field的值:
                Object value = field.get(person);
                // 如果值是String:
                if (value instanceof String) {
                    String s = (String) value;
                    // 判断值是否满足@Range的min/max:
                    if (s.length() < range.min() || s.length() > range.max()) {
                        throw new IllegalArgumentException("Invalid field: " + field.getName());
                    }
                }else{
                    int s = (int) value;
                    if (s < range.min() || s > range.max()) {
                        throw new IllegalArgumentException("Invalid field: " + field.getName());
                    }
            }
            }
        }
    }
}
```

### 1.2.4. 泛型

- 泛型就是编写模板代码来适应任意类型；编写泛型时，需要定义泛型类型`<T>`；
- 泛型的好处是使用时不必对类型进行强制转换，它通过编译器对类型进行检查；
- 注意泛型的继承关系：可以把`ArrayList<Integer>`向上转型为`List<Integer>`（T不能变！），但不能把`ArrayList<Integer>`向上转型为`ArrayList<Number>`（T不能变成父类）。
- 使用泛型时，把泛型参数`<T>`替换为需要的class类型，例如：`ArrayList<String>，ArrayList<Number>`等；
- 可以省略编译器能自动推断出的类型，例如：`List<String> list = new ArrayList<>();`；
- 不指定泛型参数类型时，编译器会给出警告，且只能将`<T>`视为Object类型；
- 可以在接口中定义泛型类型，实现此接口的类必须实现正确的泛型类型。
- 类内的静态方法不能引用泛型类型`<T>`，必须定义其他类型（例如`<K>`）来实现静态泛型方法；
- 泛型可以同时定义多种类型，例如`Map<K, V>`。

- Java的泛型是采用擦拭法实现的；所谓擦拭法是指，虚拟机对泛型其实一无所知，所有的工作都是编译器做的。编译器把类型`<T>`视为Object；编译器根据`<T>`实现安全的强制转型。
- 擦拭法决定了泛型`<T>`：
  - 不能是基本类型，例如：int；
  - 不能获取带泛型类型的Class，例如：`Pair<String>.class`；
  - 不能判断带泛型类型的类型，例如：`x instanceof Pair<String>`；
  - 不能实例化T类型，例如：`new T()`。
- 泛型方法要防止重复定义方法，例如：`public boolean equals(T obj)`；
- 子类可以获取父类的泛型类型`<T>`。
                      ┌────┐
                      │Type│
                      └────┘
                         ▲
                         │
   ┌────────────┬────────┴─────────┬───────────────┐
   │            │                  │               │
┌─────┐┌─────────────────┐┌────────────────┐┌────────────┐
│Class││ParameterizedType││GenericArrayType││WildcardType│
└─────┘└─────────────────┘└────────────────┘└────────────┘

- extends和super,使用extends和super通配符要遵循PECS原则。Producer Extends Consumer Super.如果需要返回T，它是生产者（Producer），要使用extends通配符；如果需要写入T，它是消费者（Consumer），要使用super通配符。
- extends
  - 允许调用读方法`T get()`获取T的引用，但不允许调用写方法`set(T)`传入T的引用（传入null除外）；
  - 使用类似`<T extends Number>`定义泛型类时表示：泛型类型限定为Number以及Number的子类。
- super
  - 允许调用写方法`set(T)`传入T的引用，但不允许调用读方法`T get()`获取T的引用（获取Object除外）
  - 使用类似`<T super Number>`定义泛型类时表示：泛型类型限定为Number以及Number的父类。
- 无限定通配符<?>很少使用，可以用`<T>`替换，同时它是所有`<T>`类型的超类。
- 部分反射API是泛型，例如：`Class<T>，Constructor<T>`；
- 可以声明带泛型的数组，但不能直接创建带泛型的数组，必须强制转型；
- 可以通过`Array.newInstance(Class<T>, int)`创建T[]数组，需要强制转型；
- 同时使用泛型和可变参数时需要特别小心。

### 1.2.5. 日期和时间

- 在编写日期和时间的程序前，我们要准确理解日期、时间和时刻的概念。
- 由于存在本地时间，我们需要理解时区的概念，并且必须牢记由于夏令时的存在，同一地区用GMT/UTC和城市表示的时区可能导致时间不同。所谓夏令时，就是夏天开始的时候，把时间往后拨1小时，夏天结束的时候，再把时间往前拨1小时。我们国家实行过一段时间夏令时，1992年就废除了，但是矫情的美国人到现在还在使用，所以时间换算更加复杂。实行夏令时的不同地区，进入和退出夏令时的时间很可能是不同的。同一个地区，根据历史上是否实行过夏令时，标准时间在不同年份换算成当地时间也是不同的。因此，计算夏令时，没有统一的公式，必须按照一组给定的规则来算，并且，该规则要定期更新。
- 计算机通过Locale来针对当地用户习惯格式化日期、时间、数字、货币等。

- 计算机表示的时间是以整数表示的时间戳存储的，即Epoch Time，Java使用long型来表示以毫秒为单位的时间戳，通过System.currentTimeMillis()获取当前时间戳。
- Java有两套日期和时间的API，分别位于java.util和java.time包中。
  - 旧的Date、Calendar和TimeZone；
  - 新的LocalDateTime、ZonedDateTime、ZoneId等。

#### 1.2.5.1. Data/Calendar/TimeZone

- System.currentTimeMillis()获取当前系统时间
- Data/SimpleDateFormat
  - `Date date = new Date();`getYear()返回的年份必须加上1900，getMonth()返回的月份是0~11分别表示1~12月，所以要加1，而getDate()返回的日期范围是1~31，又不能加1。
    - `System.out.println(date.getYear() + 1900);` // 必须加上1900
    - `System.out.println(date.getMonth() + 1);` // 0~11，必须加上1
    - `System.out.println(date.getDate());` // 1~31，不能加1
    - Date对象有几个严重的问题
      - 它不能转换时区，除了toGMTString()可以按GMT+0:00输出外，Date总是以当前计算机系统的默认时区为基础进行输出。
      - 此外，我们也很难对日期和时间进行加减，计算两个日期相差多少天，计算某个月第一个星期一的日期等。
  - `SimpleDateFormat`
    - 对一个Date进行转换。它用预定义的字符串表示格式化
    - yyyy：年
    - MM：月,比如9月，M：输出9，MM：输出09，MMM：输出Sep，MMMM：输出September
    - dd: 日
    - HH: 小时
    - mm: 分钟
    - ss: 秒
    - 可以进行时区转换

- Calendar
  - 可以用于获取并设置年、月、日、时、分、秒，它和Date比，主要多了一个可以做简单的日期和时间运算的功能。
  - Calendar只有一种方式获取，即Calendar.getInstance()，而且一获取到就是当前时间。
  - 如果我们想给它设置成特定的一个日期和时间，就必须先清除所有字段
  - Calendar获取年月日这些信息变成了get(int field)，返回的年份不必转换，返回的月份仍然要加1，返回的星期要特别注意，1~7分别表示周日，周一，……，周六。
  - 利用Calendar.getTime()可以将一个Calendar对象转换成Date对象

- TimeZone
  - 时区的唯一标识是以字符串表示的ID，我们获取指定TimeZone对象也是以这个ID为参数获取
  - GMT+09:00、Asia/Shanghai都是有效的时区ID。要列出系统支持的所有ID，请使用TimeZone.getAvailableIDs()。
  - TimeZone tzDefault = TimeZone.getDefault(); // 当前时区
  - System.out.println(tzDefault.getID()); // Asia/Shanghai
  - TimeZone tzGMT9 = TimeZone.getTimeZone("GMT+09:00"); // GMT+9:00时区
  - System.out.println(tzNY.getID()); // America/New_York

```java
public class Main {
    public static void main(String[] args) {
        Calendar c = Calendar.getInstance();// 可以进行时区转换
        c.clear();// 清除所有
        c.set(2019, 10 /* 11月 */, 20, 8, 15, 0);// 设置年月日时分秒
        c.add(Calendar.DAY_OF_MONTH, 5);// 加5天
        c.add(Calendar.HOUR_OF_DAY, -2);// 减去2小时
        var sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");// 显示时间:
        Date d = c.getTime();
        System.out.println(sdf.format(d));//转换-// 2019-11-25 6:15:00
    }
}
```

#### 1.2.5.2. LocalDateTime/ZonedDateTime/ZoneId/Instant

┌─────────────┐
│LocalDateTime│────┐
└─────────────┘    │    ┌─────────────┐
                   ├───>│ZonedDateTime│
┌─────────────┐    │    └─────────────┘
│   ZoneId    │────┘           ▲
└─────────────┘      ┌─────────┴─────────┐
                     │                   │
                     ▼                   ▼
              ┌─────────────┐     ┌─────────────┐
              │   Instant   │<───>│    long     │
              └─────────────┘     └─────────────┘

- 从Java 8开始，java.time包提供了新的日期和时间API，主要涉及的类型有：
  - 本地日期和时间：LocalDateTime，LocalDate，LocalTime；
  - 带时区的日期和时间：ZonedDateTime；
  - 时刻：Instant；
  - 时区：ZoneId，ZoneOffset；
  - 时间间隔：Duration。
  - 格式化类型: DateTimeFormatter

- 注意ISO 8601规定的日期和时间分隔符是T。标准格式如下：
  - 日期：yyyy-MM-dd
  - 时间：HH:mm:ss
  - 带毫秒的时间：HH:mm:ss.SSS
  - 日期和时间：yyyy-MM-dd'T'HH:mm:ss
  - 带毫秒的日期和时间：yyyy-MM-dd'T'HH:mm:ss.SSS

- LocalDateTime、LocalDate和LocalTime默认严格按照ISO 8601规定的日期和时间格式进行打印。
  - 使用LocalDateTime可以非常方便地对日期和时间进行加减，或者调整日期和时间，它总是返回新对象；
  - 使用isBefore()和isAfter()可以判断日期和时间的先后；
  - 使用Duration和Period可以表示两个日期和时间的“区间间隔”。
  - LocalDateTime无法与时间戳进行转换，因为LocalDateTime没有时区，无法确定某一时刻。

- ZonedDateTime是带时区的日期和时间，可用于时区转换；
  - ZonedDateTime和LocalDateTime可以相互转换。
  - 可以简单地把ZonedDateTime理解成LocalDateTime加ZoneId。ZoneId是java.time引入的新的时区类
  - 创建方式
    - ZonedDateTime zbj = ZonedDateTime.now(); // 默认时区
    - ZonedDateTime zny = ZonedDateTime.now(ZoneId.of("America/New_York")); // 用指定时区获取当前时间
    - LocalDateTime ldt = LocalDateTime.of(2019, 9, 15, 15, 16, 17);
    - ZonedDateTime zbj = ldt.atZone(ZoneId.systemDefault());
    - ZonedDateTime zny = ldt.atZone(ZoneId.of("America/New_York"));
  - 时区转换，涉及到时区时，千万不要自己计算时差，否则难以正确处理夏令时。
    - 要特别注意，时区转换的时候，由于夏令时的存在，不同的日期转换的结果很可能是不同的。
    - 这是北京时间9月15日的转换结果：
      - 2019-09-15T21:05:50.187697+08:00[Asia/Shanghai]
      - 2019-09-15T09:05:50.187697-04:00[America/New_York]
    - 这是北京时间11月15日的转换结果：
      - 2019-11-15T21:05:50.187697+08:00[Asia/Shanghai]
      - 2019-11-15T08:05:50.187697-05:00[America/New_York]
    - 两次转换后的纽约时间有1小时的夏令时时差。

```java
public class Main {
    public static void main(String[] args) {
        ZonedDateTime zbj = ZonedDateTime.now(ZoneId.of("Asia/Shanghai"));// 以中国时区获取当前时间
        ZonedDateTime zny = zbj.withZoneSameInstant(ZoneId.of("America/New_York"));// 转换为纽约时间
        System.out.println(zbj);
        System.out.println(zny);
    }
}

```

- DateTimeFormatter
  - 对ZonedDateTime或LocalDateTime进行格式化，需要使用DateTimeFormatter类；
  - DateTimeFormatter可以通过格式化字符串和Locale对日期和时间进行定制输出。
  - SimpleDateFormat不是线程安全的。而DateTimeFormatter是线程安全的。
  - DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
  - DateTimeFormatter formatter = DateTimeFormatter.ofPattern("E, yyyy-MMMM-dd HH:mm", Locale.US);
  - 当我们直接调用System.out.println()对一个ZonedDateTime或者LocalDateTime实例进行打印的时候，实际上，调用的是它们的toString()方法，默认的toString()方法显示的字符串就是按照ISO 8601格式显示的

- Instant表示高精度时间戳，它可以和ZonedDateTime以及long互相转换。
  - 一个是以秒为单位的时间戳，一个是更精确的纳秒精度。它和System.currentTimeMillis()返回的long相比，只是多了更高精度的纳秒。
  - 既然Instant就是时间戳，那么，给它附加上一个时区，就可以创建出ZonedDateTime
  - Instant now = Instant.now();
    - System.out.println(now.getEpochSecond()); // 秒
    - System.out.println(now.toEpochMilli()); // 毫秒

#### 1.2.5.3. 新旧API及数据库时间相关

- 处理日期和时间时，尽量使用新的java.time包；
  - 在数据库中存储时间戳时，尽量使用long型时间戳，它具有省空间，效率高，不依赖数据库的优点。
  - 旧API转新API
    - 如果要把旧式的Date或Calendar转换为新API对象，可以通过toInstant()方法转换为Instant对象，再继续转换为ZonedDateTime
      - Instant ins1 = new Date().toInstant();//默认本地时区转换
      - Instant ins2 = Calendar.getInstance().toInstant();
      - ZonedDateTime zdt = ins2.atZone(calendar.getTimeZone().toZoneId());
  - 新API转旧API,见下边代码

```java
// ZonedDateTime -> long:
ZonedDateTime zdt = ZonedDateTime.now();
long ts = zdt.toEpochSecond() * 1000;

// long -> Date:
Date date = new Date(ts);

// long -> Calendar:
Calendar calendar = Calendar.getInstance();
calendar.clear();
calendar.setTimeZone(TimeZone.getTimeZone(zdt.getZone().getId()));
calendar.setTimeInMillis(zdt.toEpochSecond() * 1000);
```

在使用Java程序操作数据库时，我们需要把数据库类型与Java类型映射起来。下表是数据库类型与Java新旧API的映射关系：
| 数据库    | 对应Java类（旧）   | 对应Java类（新） |
| --------- | ------------------ | ---------------- |
| DATETIME  | java.util.Date     | LocalDateTime    |
| DATE      | java.sql.Date      | LocalDate        |
| TIME      | java.sql.Time      | LocalTime        |
| TIMESTAMP | java.sql.Timestamp | LocalDateTime    |

### 1.2.6. 集合

- Java的集合类定义在java.util包中，支持泛型，主要提供了3种集合类，包括List，Set和Map。Java集合使用统一的Iterator遍历，尽量不要使用遗留接口。(Hashtable：一种线程安全的Map实现；Vector：一种线程安全的List实现；Stack：基于Vector实现的LIFO的栈。`Enumeration<E>`：已被`Iterator<E>`取代)。

#### 1.2.6.1. List

- List
  - `List<E>`是接口，实现List接口并非只能通过数组（即ArrayList的实现方式）来实现，另一种LinkedList通过“链表”也实现了List接口。
  - 在末尾添加一个元素：`void add(E e)`，List还允许添加null
  - 在指定索引添加一个元素：`void add(int index, E e)`
  - 删除指定索引的元素：`int remove(int index)`
  - 删除某个元素：`int remove(Object e)`
  - 获取指定索引的元素：`E get(int index)`
  - 获取链表大小（包含元素的个数）：`int size()`
  - 创建List，`List<String> list = new ArrayList<>();`,`List<String> list = new LinkedList<>();`,`List<Integer> list = List.of(1, 2, 5);`List.of()方法不接受null值
  - 使用迭代器Iterator来访问List。Iterator本身也是一个对象,boolean hasNext()判断是否有下一个元素，E next()返回下一个元素。
  - List转Array：
    - `List<String> list = List.of("apple", "pear", "banana");`
    - `Object[] array = list.toArray();`
    - `Integer[] array = list.toArray(new Integer[3]);`如果传入的数组不够大，那么List内部会创建一个新的刚好够大的数组，填充后返回；如果传入的数组比List元素还要多，那么填充完元素后，剩下的数组元素一律填充null。
    - `Integer[] array = list.toArray(new Integer[list.size()]);`
    - `Integer[] array = list.toArray(Integer[]::new);`
  - Array转List：
    - 返回的List不一定就是ArrayList或者LinkedList，因为List只是一个接口，如果我们调用List.of()，它返回的是一个只读List
    - `Integer[] array = { 1, 2, 3 };`
    - `List<Integer> list = List.of(array);`
    - `List<Integer> list = Arrays.asList(array);`
  - 重写equals()，类似C++的重载
    - 在List中查找元素时，List的实现类通过元素的equals()方法比较两个元素是否相等，因此，放入的元素必须正确覆写equals()方法，Java标准库提供的String、Integer等已经覆写了equals()方法；
    - 编写equals()方法可借助Objects.equals()判断。
    - 如果不在List中查找元素，就不必覆写equals()方法。

#### 1.2.6.2. Map/Properties

- Map
  - Map也是一个接口，最常用的实现类是HashMap。
  - Map是一种映射表，可以通过key快速查找value。
  - 可以通过for each遍历keySet()，也可以通过for each遍历entrySet()，直接获取key-value。
  - `Map<String, Student> map = new HashMap<>();`
  - `map.put("Xiao Ming", s);`put()方法的签名是V put(K key, V value)，如果放入的key已经存在，put()方法会返回被删除的旧的value，否则，返回null。
  - `Student target = map.get("Xiao Ming");`
  - `for (String key : map.keySet())    for (Map.Entry<String, Integer> entry : map.entrySet())`
  - 如果只是想查询某个key是否存在，可以调用boolean containsKey(K key)方法。
  - 要正确使用HashMap，作为key的类必须正确覆写equals()和hashCode()方法；

- EnumMap
  - 如果Map的key是enum类型，推荐使用EnumMap，既保证速度，也不浪费空间。
  - 使用EnumMap的时候，根据面向抽象编程的原则，应持有Map接口。

- SortedMap
  - 它在内部会对Key进行排序，这种Map就是SortedMap。注意到SortedMap是接口，它的实现类是TreeMap。
  - SortedMap在遍历时严格按照Key的顺序遍历，最常用的实现类是TreeMap；
  - 作为SortedMap的Key必须实现Comparable接口，或者传入Comparator；
  - 要严格按照compare()规范实现比较逻辑，否则，TreeMap将不能正常工作。

- Properties
  - Java集合库提供的Properties用于读写配置文件.properties。.properties文件可以使用UTF-8编码。
  - 可以从文件系统、classpath或其他任何地方读取.properties文件。
  - 读写Properties时，注意仅使用getProperty()和setProperty()方法，不要调用继承而来的get()和put()等方法。
  - `Properties props = new Properties();props.load(new java.io.FileInputStream(f));String filepath = props.getProperty("last_open_file");`

#### 1.2.6.3. Set

- Set
  - Set用于存储不重复的元素集合：
  - 遍历SortedSet按照元素的排序顺序遍历，也可以自定义排序算法。
  - 将元素添加进`Set<E>：boolean add(E e)`
  - 将元素从`Set<E>`删除：`boolean remove(Object e)`
  - 判断是否包含元素：`boolean contains(Object e)`
       ┌───┐
       │Set│
       └───┘
         ▲
    ┌────┴─────┐
    │          │
┌───────┐ ┌─────────┐
│HashSet│ │SortedSet│
└───────┘ └─────────┘
               ▲
               │
          ┌─────────┐
          │ TreeSet │
          └─────────┘

#### 1.2.6.4. Queue/Deque/PriorityQueue/Stack

- Queue
  - 队列Queue实现了一个先进先出（FIFO）的数据结构：
  - int size()：获取队列长度；
  - boolean add(E)/boolean offer(E)：添加元素到队尾；前者抛异常，后者返回失败
  - E remove()/E poll()：获取队首元素并从队列中删除；前者抛异常，后者返回失败
  - E element()/E peek()：获取队首元素但并不从队列中删除。前者抛异常，后者返回失败
  - LinkedList 即实现了List接口，又实现了Queue接口

- PriorityQueue
  - PriorityQueue实现了一个优先队列：从队首获取元素时，总是获取优先级最高的元素。
  - PriorityQueue默认按元素比较的顺序排序（必须实现Comparable接口），也可以通过Comparator自定义排序算法（元素就不必实现Comparable接口）。

- Deque
  - 既可以添加到队尾，也可以添加到队首；既可以从队首获取，又可以从队尾获取。
  - Deque是一个接口，它的实现类有ArrayDeque和LinkedList。

| 功能               | Queue                  | Deque                           |
| ------------------ | ---------------------- | ------------------------------- |
| 添加元素到队尾     | add(E e) / offer(E e)  | addLast(E e) / offerLast(E e)   |
| 取队首元素并删除   | E remove() / E poll()  | E removeFirst() / E pollFirst() |
| 取队首元素但不删除 | E element() / E peek() | E getFirst() / E peekFirst()    |
| 添加元素到队首     | 无                     | addFirst(E e) / offerFirst(E e) |
| 取队尾元素并删除   | 无                     | E removeLast() / E pollLast()   |
| 取队尾元素但不删除 | 无                     | E getLast() / E peekLast()      |

- Stack
  - 把元素压栈：push(E)；
  - 把栈顶的元素“弹出”：pop(E)；
  - 取栈顶元素但不弹出：peek(E)。
  - Java中的Stack继承Vector，而Vector是由数组实现的集合类，所以是低效的，建议别直接使用Java的Stack。
  - 用Deque可以实现Stack的功能，注意只调用 push()/pop()/peek() 方法，避免调用Deque的其他方法。

#### 1.2.6.5. Iterator/Collections

- Iterator
  - 集合类实现Iterable接口，该接口要求返回一个Iterator对象；
  - 用Iterator对象迭代集合内部数据。
  - Java提供了标准的迭代器模型，即集合类实现java.util.Iterable接口，返回java.util.Iterator实例。

- Collections
  - 创建空集合；/创建单元素集合；/创建不可变集合；/排序/洗牌/线程安全等操作。
  - 是JDK提供的工具类，同样位于java.util包中。它提供了一系列静态方法，能更方便地操作各种集合。
  - Collections可以对List进行排序。Collections.sort(list);
  - Collections提供了洗牌算法.Collections.shuffle(list);
  - 封装成不可变List：`List<T> unmodifiableList(List<? extends T> list)`
  - 封装成不可变Set：`Set<T> unmodifiableSet(Set<? extends T> set)`
  - 封装成不可变Map：`Map<K, V> unmodifiableMap(Map<? extends K, ? extends V> m)`
    然而，继续对原始的可变List进行增删是可以的，并且，会直接影响到封装后的“不可变”List

### 1.2.7. IO

#### 1.2.7.1. File

- Java标准库的java.io.File对象表示一个文件或者目录
  - 创建File对象本身不涉及IO操作；
  - 可以获取路径／绝对路径／规范路径：getPath()/getAbsolutePath()/getCanonicalPath()；
  - 可以获取目录的文件和子目录：list()/listFiles()；
  - 可以创建或删除文件和目录。
  - Java标准库还提供了一个Path对象，它位于java.nio.file包。Path对象和File对象类似，但操作更加简单
  - isFile()，判断该File对象是否是一个已存在的文件
  - isDirectory()，判断该File对象是否是一个已存在的目录
  - boolean mkdir()：创建当前File对象表示的目录；
  - boolean mkdirs()：创建当前File对象表示的目录，并在必要时将不存在的父目录也创建出来；
  - boolean delete()：删除当前File对象表示的目录，当前目录必须为空才能删除成功。
  - boolean canRead()：是否可读；
  - boolean canWrite()：是否可写；
  - boolean canExecute()：是否可执行；
  - long length()：文件字节大小。
  - File.separator; // 根据当前平台打印"\"或"/"

#### 1.2.7.2. InputStream/OutputStream

- Java标准库的java.io.InputStream定义了所有输入流的超类，是一个抽象类
  - FileInputStream实现了文件流输入；
  - ByteArrayInputStream在内存中模拟一个字节流输入。
  - 总是使用try(resource)来保证InputStream正确关闭。实际上，编译器并不会特别地为InputStream加上自动关闭。编译器只看try(resource = ...)中的对象是否实现了java.lang.AutoCloseable接口，如果实现了，就自动加上finally语句并调用close()方法。InputStream和OutputStream都实现了这个接口，因此，都可以用在try(resource)中。
  - read()： 读取输入流的下一个字节，并返回字节表示的int值（0~255）。如果已读到末尾，返回-1表示不能继续读取了。read()方法是阻塞（Blocking）的。
  - int read(byte[] b)：读取若干字节并填充到byte[]数组，返回读取的字节数
  - int read(byte[] b, int off, int len)：指定byte[]数组的偏移量和最大填充数
- Java标准库的java.io.OutputStream定义了所有输出流的超类：
  - FileOutputStream实现了文件流输出；
  - ByteArrayOutputStream在内存中模拟一个字节流输出。
  - 某些情况下需要手动调用OutputStream的flush()方法来强制输出缓冲区。
  - 总是使用try(resource)来保证OutputStream正确关闭。

#### 1.2.7.3. Filter/Decorator

- Java的IO标准库使用Filter模式为InputStream和OutputStream增加功能：
  - 可以把一个InputStream和任意个FilterInputStream组合；
  - 可以把一个OutputStream和任意个FilterOutputStream组合。
  - Filter模式可以在运行期动态增加功能（又称装饰器模式Decorator模式）。
  - `InputStream file = new FileInputStream("test.gz");`
  - `InputStream buffered = new BufferedInputStream(file);`
  - `InputStream gzip = new GZIPInputStream(buffered);`

无论我们包装多少次，得到的对象始终是InputStream，我们直接用InputStream来引用它，就可以正常读取：
┌─────────────────────────┐
│GZIPInputStream          │
│┌───────────────────────┐│
││BufferedFileInputStream││
││┌─────────────────────┐││
│││   FileInputStream   │││
││└─────────────────────┘││
│└───────────────────────┘│
└─────────────────────────┘

- Zip
  - ZipInputStream可以读取zip格式的流，ZipOutputStream可以把多份数据写入zip包；
  - 配合FileInputStream和FileOutputStream就可以读写zip文件。
  - ZipInputStream是一种FilterInputStream

- PrintStream是一种能接收各种数据类型的输出，打印数据时比较方便：
  - System.out是标准输出；
  - System.err是标准错误输出。
  - PrintWriter是基于Writer的输出。PrintStream最终输出的总是byte数据，而PrintWriter则是扩展了Writer接口，它的print()/println()方法最终输出的是char数据。

#### 1.2.7.4. Reader/Writer

- Reader定义了所有字符输入流的超类：
  - FileReader实现了文件字符流输入，使用时需要指定编码；
  - CharArrayReader和StringReader可以在内存中模拟一个字符流输入。
  - Reader是基于InputStream构造的：可以通过InputStreamReader在指定编码的同时将任何InputStream转换为Reader。
  - 总是使用try (resource)保证Reader正确关闭。

- Writer定义了所有字符输出流的超类：
  - FileWriter实现了文件字符流输出；
  - CharArrayWriter和StringWriter在内存中模拟一个字符流输出。
  - 使用try (resource)保证Writer正确关闭。
  - Writer是基于OutputStream构造的，可以通过OutputStreamWriter将OutputStream转换为Writer，转换时需要指定编码。

#### 1.2.7.5. ohter

- 把资源存储在classpath中可以避免文件路径依赖；
  - Class对象的getResourceAsStream()可以从classpath中读取指定资源；
  - 根据classpath读取资源时，需要检查返回的InputStream是否为null。

- 序列化和反序列化
  - 序列化是指把一个Java对象变成二进制内容，本质上就是一个byte[]数组。
    - 反序列化，即把一个二进制内容`（也就是byte[]数组）变回Java对象。有了反序列化，保存到文件中的byte[]`数组又可以“变回”Java对象
  - 可序列化的Java对象必须实现java.io.Serializable接口，类似Serializable这样的空接口被称为“标记接口”（Marker Interface）；
  - 反序列化时不调用构造方法，可设置serialVersionUID作为版本号（非必需）
  - Java的序列化机制仅适用于Java，如果需要与其它语言交换数据，必须使用通用的序列化方法，例如JSON。

### 1.2.8. 单元测试

- JUnit
  - JUnit是一个单元测试框架，专门用于运行我们编写的单元测试：
  - 一个JUnit测试包含若干`@Test`方法，并使用Assertions进行断言，注意浮点数assertEquals()要指定delta。
  - 当我们已经编写了一个Factorial.java文件后，我们想对其进行测试，需要编写一个对应的FactorialTest.java文件，以Test为后缀是一个惯例，并分别将其放入src和test目录中。
  
- Fixture组
  - 编写Fixture是指针对每个@Test方法，编写@BeforeEach方法用于初始化测试资源，编写@AfterEach用于清理测试资源；
  - 必要时，可以编写@BeforeAll和@AfterAll，使用静态变量来初始化耗时的资源，并且在所有@Test方法的运行前后仅执行一次。
  - 核心测试方法testFact()加上了@Test注解，这是JUnit要求的，它会把带有@Test的方法识别为测试方法。
  - 注意到每次运行一个@Test方法前，JUnit首先创建一个XxxTest实例，因此，每个@Test方法内部的成员变量都是独立的，不能也无法把成员变量的状态从一个@Test方法带到另一个@Test方法。

- assert条件
  - assertTrue(): 期待结果为true
  - assertFalse(): 期待结果为false
  - assertNotNull(): 期待结果为非null
  - assertArrayEquals(): 期待结果为数组并与期望数组每个元素的值均相等
  - assertThrows(): 期待捕获到指定类型的异常
  - ...

- 参数化测试
  - 可以提供一组测试数据，对一个测试方法反复测试。参数既可以在测试代码中写死，也可以通过@CsvFileSource放到外部的CSV文件中。
  - `@ParameterizedTest`: 代替`@Test`，需要提供数据源，方式如下
    - 通过`@ValueSource`提供一组数据
    - 通过`@MethodSource`注解，它允许我们编写一个同名的静态方法来提供测试参数
    - 通过`@CsvSource`，它的每一个字符串表示一行，一行包含的若干参数用,分隔
    - 通过`@CsvFileSource(resources = { "/test-capitalize.csv" })`导入测试文件

- 条件测试
  - `@EnabledOnOs(OS.WINDOWS),@EnabledOnOs({ OS.LINUX, OS.MAC })` 指定系统
  - `@Disabled` 不允许，但是结果中会统计
  - `@DisabledOnJre(JRE.JAVA_8)`只能在Java 9或更高版本执行的测试
  - `@EnabledIfSystemProperty(named = "os.arch", matches = ".*64.*")`只能在64位操作系统上执行的测试
  - `@EnabledIfEnvironmentVariable(named = "DEBUG", matches = "true")` 需要传入环境变量DEBUG=true才能执行的测试
  - `@EnableIf` 可以执行任意Java语句并根据返回的boolean决定是否执行测试,比如：`@EnabledIf("java.time.LocalDate.now().getDayOfWeek()==java.time.DayOfWeek.SUNDAY")`

### 1.2.9. 多线程

#### 1.2.9.1. Thread

- Java用Thread对象表示一个线程，通过调用start()启动一个新线程；
- 一个线程对象只能调用一次start()方法；
- 线程的执行代码写在run()方法中；
- 线程调度由操作系统决定，程序本身无法决定调度顺序；
- Thread.sleep()可以把当前线程暂停一段时间。

- Java线程对象Thread的状态包括：New、Runnable、Blocked、Waiting、Timed Waiting和Terminated；
- 通过对另一个线程对象调用join()方法可以等待其执行结束；
- 可以指定等待时间，超过等待时间线程仍然没有结束就不再等待；
- 对已经运行结束的线程调用join()方法会立刻返回。

- 对目标线程调用interrupt()方法可以请求中断一个线程，目标线程通过检测isInterrupted()标志获取自身是否已中断。如果目标线程处于等待状态，该线程会捕获到InterruptedException；
- 目标线程检测到isInterrupted()为true或者捕获了InterruptedException都应该立刻结束自身线程；
- 通过标志位判断需要正确使用volatile关键字；volatile关键字解决了共享变量在线程间的可见性问题。

- 守护线程是为其他线程服务的线程；`setDaemon(true)`;
- 所有非守护线程都执行完毕后，虚拟机退出；
- 守护线程不能持有需要关闭的资源（如打开文件等）。

#### 1.2.9.2. 锁

- synchronized
  - 多线程同时读写共享变量时，会造成逻辑错误，因此需要通过synchronized同步；`synchronized (obj)`
  - 同步的本质就是给指定对象加锁，加锁后才能继续执行后续代码；
  - 注意加锁对象必须是同一个实例；对JVM定义的单个原子操作不需要同步。
  - JVM规范定义了几种原子操作：
    - 基本类型（long和double除外）赋值，例如：`int n = m；`
    - 引用类型赋值，例如：`List<String> list = anotherList。`
    - long和double是64位数据，JVM没有明确规定64位赋值操作是不是一个原子操作，不过在x64平台的JVM是把long和double的赋值作为原子操作实现的。
  
  - 用synchronized修饰方法可以把整个方法变为同步代码块，synchronized方法加锁对象是this；
  - Java的synchronized锁是可重入锁；
  - 避免死锁的方法是多线程获取锁的顺序要一致。
  
  - wait和notify用于多线程协调运行：
    - 在synchronized内部可以调用wait()使线程进入等待状态；
    - 必须在已获得的锁对象上调用wait()方法；
    - 在synchronized内部可以调用notify()或notifyAll()唤醒其他等待线程；
    - 必须在已获得的锁对象上调用notify()或notifyAll()方法；
    - 已唤醒的线程还需要重新获得锁后才能继续执行。

```java
class TaskQueue {
    Queue<String> queue = new LinkedList<>();

    public synchronized void addTask(String s) {
        this.queue.add(s);
        this.notifyAll();
    }

    public synchronized String getTask() throws InterruptedException {
        while (queue.isEmpty()) {
            this.wait();
        }
        return queue.remove();
    }
}
```

- ReentrantLock
  - ReentrantLock可以替代synchronized进行同步；ReentrantLock获取锁更安全；
  - 必须先获取到锁，再进入try {...}代码块，最后使用finally保证释放锁；可以使用tryLock()尝试获取锁。
  - Condition可以替代wait和notify；Condition对象必须从Lock对象获取。
  - Condition提供的await()、signal()、signalAll()原理和synchronized锁对象的wait()、notify()、notifyAll()是一致的，并且其行为也是一样的：
    - await()会释放当前锁，进入等待状态；
    - signal()会唤醒某个等待线程；
    - signalAll()会唤醒所有等待线程；
    - 唤醒线程从await()返回后需要重新获得锁。

- ReadWriteLock
  - 使用ReadWriteLock可以提高读取效率：
    - ReadWriteLock只允许一个线程写入；
    - ReadWriteLock允许多个线程在没有写入时同时读取；
    - ReadWriteLock适合读多写少的场景。
  - StampedLock
    - StampedLock提供了乐观读锁，可取代ReadWriteLock以进一步提升并发性能；
    - StampedLock是不可重入锁。

#### 1.2.9.3. 线程安全集合

- 使用java.util.concurrent包提供的线程安全的并发集合可以大大简化多线程编程：
- 多线程同时读写并发集合是安全的；尽量使用Java标准库提供的并发集合，避免自己编写同步代码。

| interface | non-thread-safe         | thread-safe                              |
| --------- | ----------------------- | ---------------------------------------- |
| List      | ArrayList               | CopyOnWriteArrayList                     |
| Map       | HashMap                 | ConcurrentHashMap                        |
| Set       | HashSet / TreeSet       | CopyOnWriteArraySet                      |
| Queue     | ArrayDeque / LinkedList | ArrayBlockingQueue / LinkedBlockingQueue |
| Deque     | ArrayDeque / LinkedList | LinkedBlockingDeque                      |

- 使用java.util.concurrent.atomic提供的原子操作可以简化多线程编程：
- 原子操作实现了无锁的线程安全；适用于计数器，累加器等。

#### 1.2.9.4. 线程池

- JDK提供了ExecutorService实现了线程池功能：
  - 线程池内部维护一组线程，可以高效执行大量小任务；在执行多个任务的时候，使用Java标准库提供的线程池是非常方便的。我们提交的任务只需要实现Runnable接口，就可以让线程池去执行
  - Executors提供了静态方法创建不同类型的ExecutorService；
  - 必须调用shutdown()关闭ExecutorService；
  - FixedThreadPool：线程数固定的线程池；
  - CachedThreadPool：线程数根据任务动态调整的线程池；
  - SingleThreadExecutor：仅单线程执行的线程池。
  - ThreadPoolExecutor: 可以指定线程池范围。
  - ScheduledThreadPool 可以定期调度多个任务。
    - `schedule(new Task("one-time"), 1, TimeUnit.SECONDS);`// 1秒后执行一次性任务:
    - `scheduleAtFixedRate(new Task("fixed-rate"), 2, 3, TimeUnit.SECONDS);`// 2秒后开始执行定时任务，每3秒执行,FixedRate是指任务总是以固定时间间隔触发，不管任务执行多长时间.
    - `scheduleWithFixedDelay(new Task("fixed-delay"), 2, 3, TimeUnit.SECONDS);`// 2秒后开始执行定时任务，以3秒为间隔执行,FixedDelay是指，上一次任务执行完毕后，等待固定的时间间隔，再执行下一次任务.

- 对线程池提交一个Callable任务，可以获得一个Future对象；
- 可以用Future在将来某个时刻获取结果。
- 一个`Future<V>`接口表示一个未来可能会返回的结果，它定义的方法有：
  - get()：获取结果（可能会等待）,在调用get()时，如果异步任务已经完成，我们就直接获得结果。如果异步任务还没有完成，那么get()会阻塞，直到任务完成后才返回结果。
  - get(long timeout, TimeUnit unit)：获取结果，但只等待指定的时间；
  - cancel(boolean mayInterruptIfRunning)：取消当前任务；
  - isDone()：判断任务是否已完成。

- CompletableFuture可以指定异步处理流程：
  - thenAccept()处理正常结果；
  - exceptional()处理异常结果；
  - thenApplyAsync()用于串行化另一个CompletableFuture；
  - anyOf()和allOf()用于并行化多个CompletableFuture。

- Fork/Join是一种基于“分治”的算法：通过分解任务，并行执行，最后合并结果得到最终结果。
  - ForkJoinPool线程池可以把一个大任务分拆成小任务并行执行，任务类必须继承自RecursiveTask或RecursiveAction。
  - 使用Fork/Join模式可以进行并行计算以提高效率。

- ThreadLocal表示线程的“局部变量”，它确保每个线程的ThreadLocal变量都是各自独立的；
  - ThreadLocal适合在一个线程的处理流程中保持上下文（避免了同一参数在所有方法中传递）；
  - 使用ThreadLocal要用try ... finally结构，并在finally中清除。

### 1.2.10. 正则表达式

- import java.util.regex.Pattern,import java.util.regex.Matcher;
- java.util.regex包，用Pattern对象匹配，匹配后获得一个Matcher对象，如果匹配成功，就可以直接从Matcher.group(index)返回子串。
- String的很多接口都是使用Pattern和Matcher实现的。
- 使用正则表达式可以
  - 判断是否匹配：String.matches()
  - 分割字符串：String.split()
  - 搜索子串：Matcher.find()
  - 替换字符串：String.replaceAll()
- 具体正则表达式规则，参考相关正则表达式内容。

```java
public class Main {
    public static void main(String[] args) {
        String s = "the quick brown fox jumps over the lazy dog.";
        String r = s.replaceAll("\\s([a-z]{4})\\s", " <b>$1</b> ");
        System.out.println(r);//the quick brown fox jumps <b>over</b> the <b>lazy</b> dog.
    }
}

public class Main {
    public static void main(String[] args) {
        String s = "the quick brown fox jumps over the lazy dog.";
        Pattern p = Pattern.compile("\\wo\\w");
        Matcher m = p.matcher(s);
        while (m.find()) {
            String sub = s.substring(m.start(), m.end());
            System.out.println(sub);
        }//row/fox/dog
    }
}

```

### 1.2.11. 加密与安全

- URL编码
  - URL编码的目的是把任意文本数据编码为%前缀表示的文本，便于浏览器和服务器处理；
  - 如果字符是A~Z，a~z，0~9以及-、_、.、*，则保持不变；
  - 如果是其他字符，先转换为UTF-8编码，然后对每个字节以%XX表示。
  - 例如：字符中的UTF-8编码是0xe4b8ad，因此，它的URL编码是%E4%B8%AD。URL编码总是大写。
  - String encoded = URLEncoder.encode("中文!", StandardCharsets.UTF_8);URLEncoder把空格字符编码成+，而现在的URL编码标准要求空格被编码为%20，不过，服务器都可以处理这两种情况。
  - String decoded = URLDecoder.decode("%E4%B8%AD%E6%96%87%21", StandardCharsets.UTF_8);
  
- Base64
  - Base64编码是对二进制数据进行编码，表示成文本格式。
  - Base64编码的目的是把任意二进制数据编码为文本，但编码后数据量会增加1/3。
  - String b64encoded = Base64.getEncoder().encodeToString(input);
  - byte[] output = Base64.getDecoder().decode("5Lit");
  - String b64encoded = Base64.getUrlEncoder().encodeToString(input);
  - byte[] output = Base64.getUrlDecoder().decode(b64encoded);
  - 如果把Base64的64个字符编码表换成32个、48个或者58个，就可以使用Base32编码，Base48编码和Base58编码。字符越少，编码的效率就会越低。

- URL编码和Base64编码都是编码算法，它们不是加密算法；

- 哈希算法
  - 哈希算法可用于验证数据完整性，具有防篡改检测的功能；
  - 常用的哈希算法有MD5、SHA-1等；
  - 用哈希存储口令时要考虑彩虹表攻击。
  - Java字符串的hashCode()就是一个哈希算法，它的输入是任意字符串，输出是固定的4字节int整数

常用的哈希算法有：
| 算法       | 输出长度（位） | 输出长度（字节） |
| ---------- | -------------- | ---------------- |
| MD5        | 128 bits       | 16 bytes         |
| SHA-1      | 160 bits       | 20 bytes         |
| RipeMD-160 | 160 bits       | 20 bytes         |
| SHA-256    | 256 bits       | 32 bytes         |
| SHA-512    | 512 bits       | 64 bytes         |
...

```java
    public static void main(String[] args) throws Exception {
        // 创建一个MessageDigest实例:
        MessageDigest md = MessageDigest.getInstance("MD5");
        // 反复调用update输入数据:
        md.update("Hello".getBytes("UTF-8"));
        md.update("World".getBytes("UTF-8"));
        byte[] result = md.digest(); // 16 bytes: 68e109f0f40ca72a15e05cc22786f8e6
        System.out.println(new BigInteger(1, result).toString(16));
    }
```

- BouncyCastle是一个开源的第三方算法提供商；
  - BouncyCastle提供了很多Java标准库没有提供的哈希算法和加密算法；
  - 使用第三方算法前需要通过Security.addProvider()注册。

- Hmac算法是一种标准的基于密钥的哈希算法，可以配合MD5、SHA-1等哈希算法，计算的摘要长度和原摘要算法长度相同。
  - Hmac算法总是和某种哈希算法配合起来用的。例如，我们使用MD5算法，对应的就是HmacMD5算法，它相当于“加盐”的MD5
  - 存储用户的哈希口令时，要加盐存储，目的就在于抵御彩虹表攻击。
  - 它的全称是Hash-based Message Authentication Code，是一种更安全的消息摘要算法。

- 对称加密算法
  - 对称加密算法使用同一个密钥进行加密和解密，常用算法有DES、AES和IDEA等；
  - 密钥长度由算法设计决定，AES的密钥长度是128/192/256位；
  - 使用对称加密算法需要指定算法名称、工作模式和填充模式。
  - 密钥长度直接决定加密强度，而工作模式和填充模式可以看成是对称加密算法的参数和格式选择。Java标准库提供的算法实现并不包括所有的工作模式和所有填充模式，但是通常我们只需要挑选常用的使用就可以了。
  - 根据算法名称/工作模式/填充模式获取Cipher实例；
  - 根据算法名称初始化一个SecretKey实例，密钥必须是指定长度；
  - 使用SerectKey初始化Cipher实例，并设置加密或解密模式；
  - 传入明文或密文，获得密文或明文。

常用的对称加密算法有：

| 算法 | 密钥长度    | 工作模式             | 填充模式                                |
| ---- | ----------- | -------------------- | --------------------------------------- |
| DES  | 56/64       | ECB/CBC/PCBC/CTR/... | NoPadding/PKCS5Padding/...              |
| AES  | 128/192/256 | ECB/CBC/PCBC/CTR/... | NoPadding/PKCS5Padding/PKCS7Padding/... |
| IDEA | 128         | ECB                  | PKCS5Padding/PKCS7Padding/...           |

- PBE就是Password Based Encryption的缩写
  - PBE的作用就是把用户输入的口令和一个安全随机的口令采用杂凑后计算出真正的密钥。
  - PBE算法通过用户口令和安全的随机salt计算出Key，然后再进行加密；
  - Key通过口令和安全的随机salt计算得出，大大提高了安全性；
  - PBE算法内部使用的仍然是标准对称加密算法（例如AES）。

- DH算法(密钥交换算法)：Diffie-Hellman算法
  - DH算法是一种密钥交换协议，DH算法解决了密钥在双方不直接传递密钥的情况下完成密钥交换.
  - DH算法没有解决中间人攻击。即甲乙双方并不能确保与自己通信的是否真的是对方。
  - 算法原理
    - 甲首选选择一个素数p，例如509，底数g，任选，例如5，随机数a，例如123，然后计算A=g^a mod p，结果是215，然后，甲发送p＝509，g=5，A=215给乙；
    - 乙方收到后，也选择一个随机数b，例如，456，然后计算B=g^b mod p，结果是181，乙再同时计算s=A^b mod p，结果是121；
    - 乙把计算的B=181发给甲，甲计算s＝B^a mod p的余数，计算结果与乙算出的结果一样，都是121。
    - a看成甲的私钥，A看成甲的公钥，b看成乙的私钥，B看成乙的公钥。DH算法的本质就是双方各自生成自己的私钥和公钥，私钥仅对自己可见，然后交换公钥，并根据自己的私钥和对方的公钥，生成最终的密钥secretKey，DH算法通过数学定律保证了双方各自计算出的secretKey是相同的。

- RSA算法（非对称加密算法）由Ron Rivest，Adi Shamir，Leonard Adleman发明，DH算法的应用。
  - 非对称加密就是加密和解密使用的不是相同的密钥，只有同一个公钥-私钥对才能正常加解密；
  - 在实际应用的时候，非对称加密总是和对称加密一起使用。RSA加密“AES口令”，AES加密内容
  - 浏览器中常用的HTTPS协议的做法，即浏览器和服务器先通过RSA交换AES口令，接下来双方通信实际上采用的是速度较快的AES对称加密，而不是缓慢的RSA非对称加密。

- 签名算法
  - 私钥加密得到的密文实际上就是数字签名，要验证这个签名是否正确，只能用私钥持有者的公钥进行解密验证。
  - 数字签名就是用发送方的私钥对原始数据进行签名，只有用发送方公钥才能通过签名验证。
  - 数字签名用于：
    - 防止伪造；
    - 防止抵赖；
    - 检测篡改。
  - 常用的数字签名算法包括：MD5withRSA／SHA1withRSA／SHA256withRSA／SHA1withDSA／SHA256withDSA／SHA512withDSA／ECDSA等。
    - 比特币的签名算法就采用了ECDSA算法，使用标准椭圆曲线secp256k1。BouncyCastle提供了ECDSA的完整实现。
    - DSA是Digital Signature Algorithm的缩写，它使用ElGamal数字签名算法。DSA只能配合SHA使用。

- 数字证书
  - 数字证书就是集合了多种密码学算法，用于实现数据加解密、身份认证、签名等多种功能的一种安全标准。
  - 数字证书可以防止中间人攻击，因为它采用链式签名认证，即通过根证书（Root CA）去签名下一级证书，这样层层签名，直到最终的用户证书。而Root CA证书内置于操作系统中，所以，任何经过CA认证的数字证书都可以对其本身进行校验，确保证书本身不是伪造的。
  - 数字证书采用链式签名管理，顶级的Root CA证书已内置在操作系统中。
  - 数字证书存储的是公钥，可以安全公开，而私钥必须严格保密。
  - 我们在上网时常用的HTTPS协议就是数字证书的应用。浏览器会自动验证证书的有效性
  - 在Java程序中，数字证书存储在一种Java专用的key store文件中，JDK提供了一系列命令来创建和管理key store。我们用下面的命令创建一个key store，并设定口令123456：
    - `keytool -storepass 123456 -genkeypair -keyalg RSA -keysize 1024 -sigalg SHA1withRSA -validity 3650 -alias mycert -keystore my.keystore -dname "CN=www.sample.com, OU=sample, O=sample, L=BJ, ST=BJ, C=CN"`
    - keyalg：指定RSA加密算法；
    - sigalg：指定SHA1withRSA签名算法；
    - validity：指定证书有效期3650天；
    - alias：指定证书在程序中引用的名称；
    - dname：最重要的CN=www.sample.com指定了Common Name，如果证书用在HTTPS中，这个名称必须与域名完全一致。
    - 执行上述命令，JDK会在当前目录创建一个my.keystore文件，并存储创建成功的一个私钥和一个证书，它的别名是mycert。
    - 有了key store存储的证书，我们就可以通过数字证书进行加解密和签名
  - 以HTTPS协议为例，浏览器和服务器建立安全连接的步骤如下：
    - 浏览器向服务器发起请求，服务器向浏览器发送自己的数字证书；
    - 浏览器用操作系统内置的Root CA来验证服务器的证书是否有效，如果有效，就使用该证书加密一个随机的AES口令并发送给服务器；
    - 服务器用自己的私钥解密获得AES口令，并在后续通讯中使用AES加密。
  - 上述流程只是一种最常见的单向验证。如果服务器还要验证客户端，那么客户端也需要把自己的证书发送给服务器验证，这种场景常见于网银等。

### 1.2.12. Maven基础

- Maven是一个Java项目的管理和构建工具
  - Maven使用pom.xml定义项目内容，并使用预设的目录结构；
  - 在Maven中声明一个依赖项可以自动下载并导入classpath；
  - Maven使用groupId，artifactId和version唯一定位一个依赖。

- Maven通过解析依赖关系确定项目所需的jar包，常用的4种scope有：compile（默认），test，runtime和provided；
- Maven从中央仓库下载所需的jar包并缓存在本地；可以通过镜像仓库加速下载。

- Maven通过lifecycle、phase和goal来提供标准的构建流程。
- 使用Maven构建项目就是执行lifecycle，执行到指定的phase为止。每个phase会执行自己默认的一个或多个goal。goal是最小任务单元。
- 最常用的构建命令是指定phase，然后让Maven执行到指定的phase：
  - mvn clean
  - mvn clean compile
  - mvn clean test
  - mvn clean package
- 通常情况，我们总是执行phase默认绑定的goal，因此不必指定goal。

- Maven通过自定义插件可以执行项目构建时需要的额外功能，使用自定义插件必须在pom.xml中声明插件及配置；
- 插件会在某个phase被执行时执行；
- 插件的配置和用法需参考插件的官方文档。
- 执行每个phase，都是通过某个插件（plugin）来执行的，Maven本身其实并不知道如何执行compile，它只是负责找到对应的compiler插件，然后执行默认的compiler:compile这个goal来完成编译。
- 下面列举了一些常用的插件
  - maven-shade-plugin：打包所有依赖包并生成可执行jar；
  - cobertura-maven-plugin：生成单元测试覆盖率报告；
  - findbugs-maven-plugin：对Java源码进行静态分析以找出潜在问题。
- 内置插件
  - clean ：对应的phase为clean
  - compiler ：对应的phase为compile
  - surefire ：对应的phase为test
  - jar ：对应的phase为package

- Maven支持模块化管理，可以把一个大项目拆成几个模块 可以通过继承在parent的pom.xml统一定义重复配置 可以通过`<modules>`编译多个模块
- 使用Maven Wrapper，可以为一个项目指定特定的Maven版本。mvnw是Maven Wrapper的缩写。
- Maven Wrapper的另一个作用是把项目的mvnw、mvnw.cmd和.mvn提交到版本库中，可以使所有开发人员使用统一的Maven版本。
- mvnw使用本工程下的mave版本，和本机其他版本无关。

### 1.2.13. 网络编程基础

| OSI    | TCP/IP     |
| ------ | ---------- |
| 应用层 | 应用层     |
| 表示层 | 应用层     |
| 会话层 | 应用层     |
| 传输层 | 传输层     |
| 网络层 | IP层       |
| 链路层 | 网络接口层 |
| 物理层 | 网络接口层 |

- 使用Java进行TCP编程时，需要使用Socket模型：
- 服务器端用ServerSocket监听指定端口；
- 客户端使用Socket(InetAddress, port)连接服务器；
- 服务器端用accept()接收连接并返回Socket；
- 双方通过Socket打开InputStream/OutputStream读写数据；
- 服务器端通常使用多线程同时处理多个客户端连接，利用线程池可大幅提升效率；
- flush()用于强制输出缓冲区到网络。

- 使用UDP协议通信时，服务器和客户端双方无需建立连接：
  - 服务器端用DatagramSocket(port)监听端口；
  - 客户端使用DatagramSocket.connect()指定远程地址和端口；
  - 双方通过receive()和send()读写数据；
  - DatagramSocket没有IO流接口，数据被直接写入byte[]缓冲区。

- 发送Email
  - 类似Outlook这样的邮件软件称为MUA：Mail User Agent，意思是给用户服务的邮件代理；
  - 邮件服务器则称为MTA：Mail Transfer Agent，意思是邮件中转的代理；
  - 最终到达的邮件服务器称为MDA：Mail Delivery Agent，意思是邮件到达的代理。
  - 电子邮件一旦到达MDA，就不再动了。实际上，电子邮件通常就存储在MDA服务器的硬盘上，然后等收件人通过软件或者登陆浏览器查看邮件。
  - MUA到MTA发送邮件的协议就是SMTP协议，它是Simple Mail Transport Protocol的缩写，使用标准端口25，也可以使用加密端口465或587。
  - 使用Java程序发送邮件时，我们无需关心SMTP协议的底层原理，只需要使用JavaMail这个标准API就可以直接发送邮件。
  - 使用JavaMail API发送邮件本质上是一个MUA软件通过SMTP协议发送邮件至MTA服务器；
  - 打开调试模式可以看到详细的SMTP交互信息；
  - 某些邮件服务商需要开启SMTP，并需要独立的SMTP登录密码。

- 接收Email
  - 接收邮件使用最广泛的协议是POP3：Post Office Protocol version 3，它也是一个建立在TCP连接之上的协议。POP3服务器的标准端口是110，如果整个会话需要加密，那么使用加密端口995。
  - 另一种接收邮件的协议是IMAP：Internet Mail Access Protocol，它使用标准端口143和加密端口993。IMAP和POP3的主要区别是，IMAP协议在本地的所有操作都会自动同步到服务器上，并且，IMAP可以允许用户在邮件服务器的收件箱中创建文件夹。
  - 使用Java接收Email时，可以用POP3协议或IMAP协议。
  - 使用POP3协议时，需要用Maven引入JavaMail依赖，并确定POP3服务器的域名／端口／是否使用SSL等，然后，调用相关API接收Email。
  - 设置debug模式可以查看通信详细内容，便于排查错误。

- HTTP编程
  - HTTP是HyperText Transfer Protocol的缩写，翻译为超文本传输协议，它是基于TCP协议之上的一种请求-响应协议。
  - Java提供了HttpClient作为新的HTTP客户端编程接口用于取代老的HttpURLConnection接口；
  - HttpClient使用链式调用并通过内置的BodyPublishers和BodyHandlers来更方便地处理数据。
  - HTTP请求的格式是固定的，它由HTTP Header和HTTP Body两部分构成。
    - 第一行总是请求方法 路径 HTTP版本
    - 后续的每一行都是固定的Header: Value格式，我们称为HTTP Header，服务器依靠某些特定的Header来识别客户端请求，例如：
    - Host：表示请求的域名，因为一台服务器上可能有多个网站，因此有必要依靠Host来识别用于请求；
    - User-Agent：表示客户端自身标识信息，不同的浏览器有不同的标识，服务器依靠User-Agent判断客户端类型；
    - Accept：表示客户端能处理的HTTP响应格式，*/*表示任意格式，text/*表示任意文本，image/png表示PNG格式的图片；
    - Accept-Language：表示客户端接收的语言，多种语言按优先级排序，服务器依靠该字段给用户返回特定语言的网页版本。
  - HTTP响应也是由Header和Body两部分组成
    - 响应的第一行总是HTTP版本 响应代码 响应说明
    - 1xx：表示一个提示性响应，例如101表示将切换协议，常见于WebSocket连接；
    - 2xx：表示一个成功的响应，例如200表示成功，206表示只发送了部分内容；
    - 3xx：表示一个重定向的响应，例如301表示永久重定向，303表示客户端应该按指定路径重新发送请求；
    - 4xx：表示一个因为客户端问题导致的错误响应，例如400表示因为Content-Type等各种原因导致的无效请求，404表示指定的路径不存在；
    - 5xx：表示一个因为服务器问题导致的错误响应，例如500表示服务器内部故障，503表示服务器暂时无法响应。
  - 对于最早期的HTTP/1.0协议，每次发送一个HTTP请求，客户端都需要先创建一个新的TCP连接，然后，收到服务器响应后，关闭这个TCP连接。
  - 为了提高效率，HTTP/1.1协议允许在一个TCP连接中反复发送-响应，这样就能大大提高效率
  - HTTP/2.0允许客户端在没有收到响应的时候，发送多个HTTP请求，服务器返回响应的时候，不一定按顺序返回，只要双方能识别出哪个响应对应哪个请求，就可以做到并行发送和接收

### 1.2.14. XML和JSON

- XML
  - 因为XML是一种树形结构的文档，它有两种标准的解析API：
    - DOM：一次性读取XML，并在内存中表示为树形结构；
    - SAX：以流的形式读取XML，使用事件回调。
  - Java提供了DOM API来解析XML，它使用下面的对象来表示XML的内容：
    - Document：代表整个XML文档；
    - Element：代表一个XML元素；
    - Attribute：代表一个元素的某个属性。
  - Java提供的DOM API可以将XML解析为DOM结构，以Document对象表示；
  - DOM可在内存中完整表示XML数据结构；
  - DOM解析速度慢，内存占用大。
  
  - SAX是一种流式解析XML的API；
  - SAX通过事件触发，读取速度快，消耗内存少；
  - 调用方必须通过回调方法获得解析过程中的数据。
  - Java使用SAXParserFactory来使用SAX读取XML
  - SAX解析会触发一系列事件：
    - startDocument：开始读取XML文档；
    - startElement：读取到了一个元素，例如`<book>`；
    - characters：读取到了字符；
    - endElement：读取到了一个结束的元素，例如`</book>`；
    - endDocument：读取XML文档结束。
  
  - 使用Jackson解析XML，可以直接把XML解析为JavaBean，十分方便。

- JSON
  - JSON作为数据传输的格式，有几个显著的优点：
    - JSON只允许使用UTF-8编码，不存在编码问题；
    - JSON只允许使用双引号作为key，特殊字符用\转义，格式简单；
    - 浏览器内置JSON支持，如果把数据用JSON发送给浏览器，可以用JavaScript直接处理。
  - JSON适合表示层次结构，因为它格式简单，仅支持以下几种数据类型：
    - 键值对：{"key": value}
    - 数组：[1, 2, 3]
    - 字符串："abc"
    - 数值（整数和浮点数）：12.34
    - 布尔值：true或false
    - 空值：null
  - 常用的用于解析JSON的第三方库有：
    - Jackson
      - Jackson可以实现JavaBean和JSON之间的转换；
      - 可以通过Module扩展Jackson能处理的数据类型；
      - 可以自定义JsonSerializer和JsonDeserializer来定制序列化和反序列化。
    - Gson
    - Fastjson

## 1.3. 参考资料

1. [Java教程](https://www.liaoxuefeng.com/wiki/1252599548343744)
