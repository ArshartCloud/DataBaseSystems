JSON数据解析过程：

以下面这组数据为例子：
{"sparse_018": "GBRDCMA=", "nested_obj": {"num": 5001, "str": "GBRDCMBQGEYTCMBQGAYTAMBR"}, "dyn2": 10001, "dyn1": 10001, "nested_arr": ["the"], "sparse_010": "GBRDCMA=", "str2": "GBRDCMBQGEYTCMBQGAYTAMBR", "str1": "GBRDCMBQGEYTCMBQGAYTAMBQGE======", "sparse_013": "GBRDCMA=", "sparse_014": "GBRDCMA=", "sparse_015": "GBRDCMA=", "sparse_016": "GBRDCMA=", "sparse_017": "GBRDCMA=", "num": 10001, "bool": true, "sparse_011": "GBRDCMA=", "thousandth": 1, "sparse_019": "GBRDCMA=", "sparse_012": "GBRDCMA="},


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
   嵌套对象单独处理，个人在tuple中增加了指针和计数器来管理当前元组属性中的嵌套对象，适用于多重嵌套。嵌套对象不写入data中，因此解释时候直接从child中读取。

5. serialization format还原为JSON数据，最后JSON数据可能与原数据在attribute的先后顺序上发生差异，因为我们对serialization format中的aid进行了排序。


