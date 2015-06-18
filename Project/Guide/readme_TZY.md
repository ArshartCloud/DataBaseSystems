### serial 数据解析过程  ###

这里的例子和周晓斌同学的用的例子相同，只是我的部分是把serializer 的数据装换回json

SERIALIZER format：（因为是二进制读取，在读取的时候所有的数字都是类似^θ 这样的乱码）

{count: 19, aid0: 3, aid1: 4, aid2: 5, aid3: 6, aid4: 7, aid5: 8, aid6: 10, aid7: 32, aid8: 33, aid9: 34, aid10: 1, aid11: 11, aid12: 35, aid13: 36, aid14: 37, aid15: 38, aid16: 39, aid17: 40, aid18: 41, offset0: 0, offset1: 0, offset2: 1, offset3: 6, offset4: 20, offset5: 44, offset6: 76, offset7: 77, offset8: 85, offset9: 93, offset10: 101, offset11: 106, offset12: 107, offset13: 115, offset14: 123, offset15: 131, offset16: 139, offset17: 147, len: 163, data: F10002before|countryGBRDCMBQGEYTCMBQGAYTAMJQGBRDCMBQGEYTCMBQGAYTAMBRGA======2GBRDCMI=GBRDCMI=GBRDCMI=10002FGBRDCMI=GBRDCMI=GBRDCMI=GBRDCMI=GBRDCMI=GBRDCMI=GBRDCMI=}, {count: 2, aid0: 1, aid1: 2, offset0: 0, len: 28, data: 5002GBRDCMBQGEYTCMBQGAYTAMJQ}

JSON format：
{"nested_obj": {"num": 5002, "str": "GBRDCMBQGEYTCMBQGAYTAMJQ"}, "dyn2": false, "dyn1": 10002, "nested_arr": ["before", "country"], "str2": "GBRDCMBQGEYTCMBQGAYTAMJQ", "str1": "GBRDCMBQGEYTCMBQGAYTAMBRGA======", "thousandth": 2, "sparse_025": "GBRDCMI=", "sparse_024": "GBRDCMI=", "sparse_027": "GBRDCMI=", "num": 10002, "bool": false, "sparse_020": "GBRDCMI=", "sparse_023": "GBRDCMI=", "sparse_022": "GBRDCMI=", "sparse_021": "GBRDCMI=", "sparse_029": "GBRDCMI=", "sparse_028": "GBRDCMI=", "sparse_026": "GBRDCMI="}

我用了
struct form {
    int count; // the total
    int cur;
    my_vector<char> data;
    my_vector<int> aid; // the number of aid
    my_vector<char*> name; // to save each aid's name
    my_vector<int> offset; // record the offsets
};

来处理数据，每次读取 一个{} 里面的内容。用count 来存 serializer 中的count，aid、offset数组分别存 serializer中的aidi、offseti 中的数字， 其中offset 数组的最后一位会储存len的内容。data是根据len的长度读取相应地字符。
再根据aid数组存的id 在catalog中找到相应地name，存到name数组中；

在读取的时候，首先判断是否是嵌套数组，通过分隔符的来读取数组的内容；
然后通过判断offset前后的差来判断是否是嵌套的结构，
    如果是则递归调用；
    否则调用函数来写入bool、数字和字符串；



###  个人心得和体会   ###

这次设计难度比第一次的要大，花的时间也比上一次的长很多。由于对文件的读写不太熟悉，然后Linux用的也不习惯（早知就用xcode了）所以一开始走了不少弯路，结果不但效率不高，而且上传代码存在许多bug，给我的队友造成了诸多的不便。

不过长时间的debug 也提高了我的检查代码的能力，后面几天看到段错误就立刻想到数组越界、看到内存泄露马上就能够把my_vector手动释放内存。所以后面几天写的bug基本上就没有了。

通过几天不断的实践，我也掌握了不少Linux的基本用法。比如vim 的使用，比如用valgrind 检查内存错误， 比如各种makefile 的写法，感觉受益良多。

另外由于我们组用的是github来管理代码，我现在已经掌握了基本的github的用法，日后自己去找项目的时候也方便多了。

######################
