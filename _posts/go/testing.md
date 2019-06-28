http://docscn.studygolang.com/pkg/testing/

1，测试单个文件，一定要带上被测试的原文件
    go test -v  wechat_test.go wechat.go 

2，测试单个方法
    go test -v -test.run TestRefreshAccessToken
	
1、测试单个文件
go test -v  file_test.go

2、测试单个文件内单个测试用例
go test -v file_test.go -test.run TestFunc