# sqlit.exe

## 简介

## 命令参数

- 加载数据库，不存在就创建 `sqlite3 dbName.db`
- 显示数据库

`sqlite> .databases`

| seq | name | file                                            |
| --- | ---- | ----------------------------------------------- |
| 0   | main | /root/workspace/SVN_AUTH/db/development.sqlite3 |

- 显示表

`sqlite> .tables`
applies            logs               repositories       users
deps               permits            schema_migrations

- 显示表的内容

`sqlite> .head on`  #显示表头
`sqlite> select * from users;`

| id  | name              | brief   | group      | dep_id | created_at                 | updated_at                 |
| --- | ----------------- | ------- | ---------- | ------ | -------------------------- | -------------------------- |
| 1   | 3B-7-1-16  刘文民 | liuwm   | superadmin |        | 2011-08-08 08:11:37.283136 | 2011-08-08 08:11:37.283136 |
| 3   | 3D-1-01  贾延平   | jiayp   | admin      |        | 2011-08-08 08:19:51.745947 | 2011-08-08 08:19:51.745947 |
| 4   | 3B-7-1-11 杜宏伟  | duhw    |            |        | 2011-08-08 08:33:51.496746 | 2011-08-08 08:33:51.496746 |
| 5   | 3B-2-14  苑辰     | yuanc-a | emplooyee  |        | 2011-08-08 08:52:03.229173 | 2011-08-08 08:52:03.229173 |
| 6   | 3B-2-16  周四维   | zhousw  |            |        | 2011-08-08 08:54:21.134175 | 2011-08-08 08:54:21.134175 |
| 7   | 3B-2-12  施晟     | shis    |            |        | 2011-08-08 08:56:01.234077 | 2011-08-08 08:56:01.234077 |

1. .help  帮助详解

`sqlite> .help`

`.backup ?DB? FILE`      Backup DB (default "main") to FILE
`.bail ON|OFF`           Stop after hitting an error.  Default OFF
`.databases`             List names and files of attached databases
`.dump ?TABLE? ...`      Dump the database in an SQL text format
                         If TABLE specified, only dump tables matching
                         LIKE pattern TABLE.
`.echo ON|OFF`           Turn command echo on or off
`.exit`                  Exit this program
`.explain ?ON|OFF?`      Turn output mode suitable for EXPLAIN on or off.
                         With no args, it turns EXPLAIN on.
`.header(s) ON|OFF`      Turn display of headers on or off
`.help`                  Show this message
`.import FILE TABLE`     Import data from FILE into TABLE
`.indices ?TABLE?`       Show names of all indices
                         If TABLE specified, only show indices for tables
                         matching LIKE pattern TABLE.
`.load FILE ?ENTRY?`     Load an extension library
`.log FILE|off`          Turn logging on or off.  FILE can be stderr/stdout
`.mode MODE ?TABLE?`     Set output mode where MODE is one of:
                         csv      Comma-separated values
                         column   Left-aligned columns.  (See .width)
                         html     HTML `<table>` code
                         insert   SQL insert statements for TABLE
                         line     One value per line
                         list     Values delimited by .separator string
                         tabs     Tab-separated values
                         tcl      TCL list elements
`.nullvalue STRING`      Print STRING in place of NULL values
`.output FILENAME`       Send output to FILENAME
`.output stdout`         Send output to the screen
`.prompt MAIN CONTINUE`  Replace the standard prompts
`.quit`                  Exit this program
`.read FILENAME`         Execute SQL in FILENAME
`.restore ?DB? FILE`     Restore content of DB (default "main") from FILE
`.schema ?TABLE?`        Show the CREATE statements
                         If TABLE specified, only show tables matching
                         LIKE pattern TABLE.
`.separator STRING`      Change separator used by output mode and .import
`.show`                  Show the current values for various settings
`.stats ON|OFF`          Turn stats on or off
`.tables ?TABLE?`        List names of tables
                         If TABLE specified, only list tables matching
                         LIKE pattern TABLE.
`.timeout MS`            Try opening locked tables for MS milliseconds
`.width NUM1 NUM2 ...`   Set column widths for "column" mode
`.timer ON|OFF`          Turn the CPU timer measurement on or off

## 参考资料

1. [sqlite3 命令行操作](https://www.cnblogs.com/lwm-1988/archive/2011/08/20/2147573.html)