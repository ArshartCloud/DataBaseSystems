### 主程序命令说明 ###

main()加载后初始化一个空的catalog。

共3条命令，插入，显示，查找。

1. insert filename("path") : 在指定路径下把json格式的记录转换成serialization format加载到内存中，并以二进制文件保存在相应的路径下，同时对所有记录进行catalog的检录。(是否所有文件都检录到同一个catalog中?需要问问TA)。

2. check catalog() : 以table形式显示catalog中的数据。

3. find(A, B) : 先到catalog中查询A的id，然后到serializer中查询**所有含此id A和同样value B的元组**，把此元组解析为JSON格式，输出。

---

### JSON数据解析过程 ###

个人设计的数据结构如下：

    struct tuple {
        int key_num;
        my_vector<int> aid;
        my_vector<int> offset;
        // length of all data, except for nested_obj
        int len;
        // key data except nested _obj
        my_string data;
        my_vector<tuple*> child;
        // number of nested_obj
        int child_num;
    };

以一条json元组记录为例：

1. 先读入key_name的名字，即"XX"中的内容，如"sparse_054"；

2. 读入key_value之前，先进行类型判断。
   若下一个字符为'"'，即该属性为字符串，"GBRDCMBQGEYTCMBQGAYTCMBR"；
   若为数字，即该属性为整数，5005；
   若为'f'或者't'，即为布尔变量，true；
   若为[, 即为嵌套数组，["we've", "this", "which", "the", "between"]；
   若为{，即为嵌套对象，{"num": 5005, "str": "GBRDCMBQGEYTCMBQGAYTCMBR"}；
   然后对key_value进行读入，读入后加入到tuple结构体当中，更新相应成员；

   关于嵌套数组，从数据来看是字符串数组，由于实现要求：写字符串的时候,注意不要包括’\0’，因此需要额外选一个分隔符来间隔字符串数组中的元素；

    前四种key都以字符形式存入data中，嵌套对象以指针方式存入向量child中。

   嵌套对象单独处理，个人在tuple中增加了指针和计数器来管理当前元组属性中的嵌套对象，适用于多重嵌套。嵌套对象不把数据写入data中，因此解析时直接从向量child中读取。


3. 在读入一条key时，需要在catalog中查询是否对该key进行了索引。规定索引的_id为正数。

   若有，对应的count加1;若无，建立索引。返回属性_id。 

4. 完整读入一条元组后，进行写入操作。


---


**以下面这组数据为例子：**

JSON format：

{"nested_obj": {"num": 5002, "str": "GBRDCMBQGEYTCMBQGAYTAMJQ"}, "dyn2": false, "dyn1": 10002, "nested_arr": ["before", "country"], "str2": "GBRDCMBQGEYTCMBQGAYTAMJQ", "str1": "GBRDCMBQGEYTCMBQGAYTAMBRGA======", "thousandth": 2, "sparse_025": "GBRDCMI=", "sparse_024": "GBRDCMI=", "sparse_027": "GBRDCMI=", "num": 10002, "bool": false, "sparse_020": "GBRDCMI=", "sparse_023": "GBRDCMI=", "sparse_022": "GBRDCMI=", "sparse_021": "GBRDCMI=", "sparse_029": "GBRDCMI=", "sparse_028": "GBRDCMI=", "sparse_026": "GBRDCMI="},


SERIALIZER format：

{count: 19, aid0: 3, aid1: 4, aid2: 5, aid3: 6, aid4: 7, aid5: 8, aid6: 10, aid7: 32, aid8: 33, aid9: 34, aid10: 1, aid11: 11, aid12: 35, aid13: 36, aid14: 37, aid15: 38, aid16: 39, aid17: 40, aid18: 41, offset0: 0, offset1: 0, offset2: 1, offset3: 6, offset4: 20, offset5: 44, offset6: 76, offset7: 77, offset8: 85, offset9: 93, offset10: 101, offset11: 106, offset12: 107, offset13: 115, offset14: 123, offset15: 131, offset16: 139, offset17: 147, len: 163, data: F10002before-countryGBRDCMBQGEYTCMBQGAYTAMJQGBRDCMBQGEYTCMBQGAYTAMBRGA======2GBRDCMI=GBRDCMI=GBRDCMI=10002FGBRDCMI=GBRDCMI=GBRDCMI=GBRDCMI=GBRDCMI=GBRDCMI=GBRDCMI=}, {count: 2, aid0: 1, aid1: 2, offset0: 0, len: 28, data: 5002GBRDCMBQGEYTCMBQGAYTAMJQ},


说明：

1. 嵌套对象的大小设为0，位移与上一个key相同。嵌套对象依次在当前元组结束后的同一行写入， 如上述元组的第二个key是嵌套对象，紧接着写在元组同一行位置。

2. aid需要进行排序以便于二分查找，同样offs也需要排序，这部分优化由你们来实现。

3. 分隔符上面暂时用的‘-’, 具体实现我会用一个名为delimiter的字符变量来表示。

4. bool变量在数据中用'T'或者'F'两个字符变量来表示。

5. serialization format还原为JSON数据，最后JSON数据可能与原数据在key的先后顺序上发生差异，因为我们对serialization format中的aid进行了排序。
