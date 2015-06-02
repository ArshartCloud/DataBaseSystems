### 主程序命令说明 ###

main()加载后初始化一个空的catalog。

共3条命令，插入，显示，查找。

1. insert filename("path") : 在指定路径下把json格式的记录转换成serialization format加载到内存中，并以二进制文件保存在相应的路径下，同时对所有记录进行catalog的检录。(是否所有文件都检录到同一个catalog中?需要问问TA)。

2. check catalog() : 以table形式显示catalog中的数据。

3. find(A, B) : 先到catalog中查询A的id，然后到serializer中查询**所有含此id A和同样value B的元组**，把此元组解析为JSON格式，输出。



---

### JSON数据解析过程 ###

1. 先读入attribute的名字，即"XX"中的内容

2. 越过格式上的 “： ”。

3. 若下一个读取字符为 “，即该属性为字符串；
   若为数字，即该属性为整数；
   若为f或者b，即为布尔变量；
   若为[, 即为嵌套数组；
   若为{，即为嵌套对象；

4. 在catalog中查询是否对该attribute进行了索引。

   若有，对应的count加1，返回属性_id。若无，建立索引，返回属性_id。 

   前三者直接在catalog中建立索引；

   嵌套数组从数据来看是字符串数组，但由于实现要求：写字符串的时候,注意不要包括’\0’(我想不明白这个要求是从于何种考虑，whatever)，因此需要额外选一个字符串的分隔符来间隔字符串数组中的元素，这个分隔符从ASCAII表中的非显示字符中选；

   嵌套对象单独处理，个人在tuple中增加了指针和计数器来管理当前元组属性中的嵌套对象，适用于多重嵌套。嵌套对象把所有数据写入data中，因此解释时候直接从child中读取。

5. serialization format还原为JSON数据，最后JSON数据可能与原数据在attribute的先后顺序上发生差异，因为我们对serialization format中的aid进行了排序。


**以下面这组数据为例子：**

JSON format：

{"nested_obj": {"num": 5007, "str": "GBRDCMBQGEYTCMBQGAYTCMJR"}, "dyn2": 10007, "dyn1": 10007, "nested_arr": ["this", "``", "achieving", "tradition", "said", "lovering", "about"], "str2": "GBRDCMBQGEYTCMBQGAYTCMJR", "str1": "GBRDCMBQGEYTCMBQGAYTAMJRGE======", "sparse_079": "GBRDCMBQGA======", "thousandth": 7, "sparse_078": "GBRDCMBQGA======", "num": 10007, "bool": true, "sparse_072": "GBRDCMBQGA======", "sparse_073": "GBRDCMBQGA======", "sparse_070": "GBRDCMBQGA======", "sparse_071": "GBRDCMBQGA======", "sparse_076": "GBRDCMBQGA======", "sparse_077": "GBRDCMBQGA======", "sparse_074": "GBRDCMBQGA======", "sparse_075": "GBRDCMBQGA======"}


SERIALIZER format：

{count: 19, aid0: -1, aid1: 1, aid2: 5, aid3: 5, aid4: 6, aid5: 7, aid6: 20, aid7: 34, aid8: 40, aid9: 68, aid10: 21, aid11: 24, aid12: 35, aid13: 24, aid14:23, aid15: 18, aid16: 87, aid17: 90, aid18: 65, offset0: 0,----， len: X, data: 1000710007this\0``\0achieving\0tradition\0said\0lovering\0aboutGBRDCMBQGEYTCMBQGAYTCMJRGBRDCMBQGEYTCMBQGAYTAMJRGE======GBRDCMBQGA======7GBRDCMBQGA======10007TGBRDCMBQGA======GBRDCMBQGA======GBRDCMBQGA======GBRDCMBQGA======GBRDCMBQGA======GBRDCMBQGA======GBRDCMBQGA======GBRDCMBQGA======}, {count: 2, aid0: 3, aid1: 8, offs0: 0, offs1: 4, len: 28, data: 5004GBRDCMBQGEYTCMBQGAYTCMJR}，



说明：

1. 嵌套对象的位移设为-1， 嵌套对象依次在当前元组结束后的同一行写入， 如上述元组的第一个key是嵌套对象，紧接着写在元组同一行位置。

2. aid需要进行排序以便于二分查找，同样offs也需要排序，这部分优化由你们来实现。

3. 分隔符上面暂时用的‘\0’, 具体实现我会用一个名为delimiter的字符变量来表示。

4. bool变量在数据中用T或者F两个字符变量来表示。


