void catalog::Find() 函数，接受两个输入（stdin）

输入key_name和key_value
两者可以输入在同一行（用' '隔开），也可以通过回车分两行输入。
输入原则：
key_name：输入不能包含空格。（以空格或回车结束）
key_value：大致遵循json格式,根据类型按下列法则输入，然后以回车结束。
int:只能输入0~9直接的字符：eg. 4507
bool：只能输入true或false：eg. true
text：以'"'作为开始和结束标志，之间输入遵循字符串原则①：eg. "GBRDCMBQ"
nested_arr: 以'['为开始和']'为结束标志，中间包含text，之间用','+' '隔开：eg. ["checking", "of", "acquired"]

①字符串原则：转义规则：不能直接输入'"'或'\'，需在之前加上额外的'\'。


tuple* catalog::sort_id(tuple* t)
将t排序并释放，返回排序后的tuple。


###  个人心得和体会   ###

一开始以为find用不了多少时间，就把find 和sort一起包揽下来了。

写sort的时候，本来想直接写void sort_id(tuple*& t) ，但不知道为什么，貌似指针没法被引用，就改成了tuple* catalog::sort_id(tuple* t)。
被排序的tuple真的是个很蛋疼的数据结构（就是 字符串……），直接对t内部排序太耗时，最后新建一个tuple返回，并删除原来的tuple。

find一开始理解错了，拆成了4个函数重载……只为输入端服务的话，应该是void find(char* A,char* B) 
就够用了，也不必把json和serialization转化成int,bool啊再比较……

反正将错就错吧……写成4个重载泛用性也能提高……
