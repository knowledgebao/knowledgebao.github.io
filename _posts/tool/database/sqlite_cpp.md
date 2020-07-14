# 1. sqlite_cpp

- [1. sqlite_cpp](#1-sqlite_cpp)
  - [1.1. 说明](#11-说明)
  - [1.2. Summary](#12-summary)
    - [1.2.1. sqlite3](#121-sqlite3)
    - [1.2.2. sqlite3_stmt](#122-sqlite3_stmt)
    - [1.2.3. sqlite3_open()](#123-sqlite3_open)
    - [1.2.4. sqlite3_prepare()](#124-sqlite3_prepare)
    - [1.2.5. sqlite3_bind()](#125-sqlite3_bind)
    - [1.2.6. sqlite3_step()](#126-sqlite3_step)
    - [1.2.7. sqlite3_column()](#127-sqlite3_column)
    - [1.2.8. sqlite3_finalize()](#128-sqlite3_finalize)
    - [1.2.9. sqlite3_close()](#129-sqlite3_close)
    - [1.2.10. sqlite3_exec()](#1210-sqlite3_exec)
  - [other sqlite3 fun](#other-sqlite3-fun)
    - [sqlite3_changes()](#sqlite3_changes)
  - [other sqlite3_stmt fun](#other-sqlite3_stmt-fun)
  - [1.3. 参考资料](#13-参考资料)

## 1.1. 说明

## 1.2. Summary

The following two objects and eight methods comprise the essential elements of the SQLite interface:

### 1.2.1. sqlite3

The database connection object. Created by sqlite3_open() and destroyed by sqlite3_close().

### 1.2.2. sqlite3_stmt

The prepared statement object. Created by sqlite3_prepare() and destroyed by sqlite3_finalize().

### 1.2.3. sqlite3_open()

Open a connection to a new or existing SQLite database. The constructor for sqlite3.

### 1.2.4. sqlite3_prepare()

Compile SQL text into byte-code that will do the work of querying or updating the database. The constructor for sqlite3_stmt.

### 1.2.5. sqlite3_bind()

Store application data into parameters of the original SQL.

### 1.2.6. sqlite3_step()

Advance an sqlite3_stmt to the next result row or to completion.

### 1.2.7. sqlite3_column()

Column values in the current result row for an sqlite3_stmt.

### 1.2.8. sqlite3_finalize()

Destructor for sqlite3_stmt.

### 1.2.9. sqlite3_close()

Destructor for sqlite3.

### 1.2.10. sqlite3_exec()

A wrapper function that does sqlite3_prepare(), sqlite3_step(), sqlite3_column(), and sqlite3_finalize() for a string of one or more SQL statements.

## other sqlite3 fun

### sqlite3_changes()

[Count The Number Of Rows Modified](https://sqlite.org/c3ref/changes.html)

- 此函数返回指定的数据库最近完成的INSERT，UPDATE或DELETE语句修改，插入或删除的行数。执行任何其他类型的SQL语句都不会修改此函数返回的值。
- 仅考虑由INSERT，UPDATE或DELETE语句直接进行的更改-不计算由触发器， 外键操作或REPLACE约束解析引起的辅助更改。
- 被 INSTEAD OF 触发器拦截的视图更改不计算在内。在视图上运行 INSERT，UPDATE 或 DELETE 语句后，sqlite3_changes()返回的值始终为零。仅计算对实际表所做的更改。
- 如果在运行触发器程序的同时执行 sqlite3_changes()函数，事情将变得更加复杂。如果程序使用changes() SQL 函数，或者某些其他回调函数直接调用 sqlite3_changes()，则可能会发生这种情况。
- 在输入触发程序之前，将保存sqlite3_changes()函数返回的值。触发程序完成后，将恢复原始值。
- 在触发器程序中，每个INSERT，UPDATE和DELETE语句都将正常完成时设置sqlite3_changes()返回的值。当然，此值将不包括由子触发器执行的任何更改，因为sqlite3_changes()值将在每个子触发器运行后被保存并恢复。
- 这意味着，如果触发器中的第一个INSERT，UPDATE或DELETE语句使用changes()SQL函数（或类似函数），则它将返回调用语句开始执行时设置的值。如果它被触发器程序中的第二条或后续此类语句使用，则返回的值将反映由同一触发器中的先前INSERT，UPDATE或DELETE语句修改的行数。
- 如果在运行sqlite3_changes()时，一个单独的线程在同一数据库连接上进行了更改，则返回的值是不可预测的，并且没有意义。

## other sqlite3_stmt fun

## 1.3. 参考资料

1. [An Introduction To The SQLite C/C++ Interface](https://sqlite.org/cintro.html)
2. [](https://sqlite.org/download.html)
