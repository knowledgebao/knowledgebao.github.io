import click
import os
import re

def list_all_files(rootdir):
    _files = []
    list = os.listdir(rootdir) #列出文件夹下所有的目录与文件
    for i in range(0,len(list)):
           path = os.path.join(rootdir,list[i])
           if os.path.isdir(path):
              _files.extend(list_all_files(path))
           if os.path.isfile(path):
              _files.append(path)
    return _files

def process_replace(file, data):
    change = False
    with open(file, "r", encoding="utf-8") as f1,open("%s.bak" % file, "w", encoding="utf-8") as f2:
        for line in f1:
                for key in data:
                    if key in line:
                        change = True
                        line = line.replace(key,data[key])
                f2.write(line)
    if change:
        os.remove(file)
        os.rename("%s.bak" % file, file)
    else:
        os.remove("%s.bak" % file)

@click.group()
def app():
    '''
    入口
    '''
    pass

g_data = {
"9 0 %":" 90% ","1 0 %":" 10% ",
"5 1 2":" 512 ","1 0 2 4":" 1024 ",
 "6 5 5 3 5":" 65535 ",
 "A C K":" ACK ",
 "A P I":" API ",
 " b a c k l o g ":" backlog ",
 "C L O S E D":" CLOSED ",
 "C L O S I N G":"CLOSING",
 "c w n d":" cwnd ",
 "E S TA B L I S H E D":" ESTABLISHED ",
 " f u l l - s i z e d":" full-sized ",
 "F T P":" FTP ",
 "F I N _ WA I T _ 1":" FIN_WAIT_1 ",
 "FI N _ W AI T _ 2":" FIN_WAIT_2 ",
 "F I N":" FIN ",
 "H a l f - O p e n":"Half-Open",
 " I C M P ":" ICMP "," I C M P":" ICMP ","I C M P ":" ICMP ","I C M P":" ICMP ",
 "I P":" IP ",
 "I S N":" ISN ",
 "k i n d":" kind ",
 "k e e p a l i v e":" keepalive ",
 "L I S T E N":" LISTEN ",
 "l e n":" len ",
 "M S S":" MSS ",
 "M S L":" MSL ",
 "N a g l e":" Nagle ",
 "P S H":" PSH ","P U S H":" PUSH ",
 "R S T":" RST ",
 "s s t h re s h":" ssthresh ",
 "R F C 7 9 3":" RFC793 ",
 "R l o g i n":" Rlogin ",
 "s o c k e t p a i r":" socketpair ",
 "s o c k e t":"socket ",
 "S O _ L I N G E R":"SO_LINGER",
 "S Y N _ S E N T":" SYN_SENT ",
 "S Y N _ R C V D":" SYN_RCVD ",
 "S Y N":" SYN ",
 "S M T P":" SMTP ",
 "S O _ R E U S E A D D R":" SO_REUSEADDR",
 "T I M E _ WA I T":" TIME_WAIT ",
 "T e l n e t":" Telnet ","Te l n e t":" Telnet ",
 "T C P":" TCP ","  TCP":" TCP",
 "T T L":" TTL ",
 "U R G":" URG ", 
 "U R G":" URG ",
 "U D P":" UDP ","  UDP":" UDP",
 " w i n d o w p r o b e ":" windowprobe ",
 "w i n d o w":" window ",
}

@app.command()
@click.option("--dir", type=click.Path(),default="../TCP协议总结")
def replace_root(dir):
    '''
    1. 替换指定目录 dir 下所有文件内容的关键字key
    2. key对应的value是替换字段
    '''
    if len(g_data):
        files = list_all_files(dir)
        process_size = 0
        extern = ['.md']
        for f in files:
            if os.path.splitext(f)[-1] in extern:
                process_replace(f,g_data)
                process_size = process_size+1

        print('total:', process_size)

if __name__ == "__main__":
    # app()
    replace_root()
