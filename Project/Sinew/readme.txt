change_back_to_json的功能就是把序列化的格式转回json
调用时要#include"change_back_to_json。h”, 然后定义tran类变量，调用print(FILE *in， FILE *out， catalog *CATALOG)函数。
注意：一次最多只能生成500kb左右的数据（不过好像要求每次转8kb所以应该没问题），所以最好每一页用一次该函数转成json。（目测指针用完没有清理结果爆内存吧。。。）