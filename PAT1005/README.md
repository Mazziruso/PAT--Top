# 题解
----
* 考察字符串匹配问题
* 采用KMP算法，pattern字符串长度固定为N；在文本字符串中搜索并统计pattern字符串出现的次数
* pattern字符串从文本字符串中从头开始遍历提取；构造出next状态机数组后从该字符串在文本字符串的位置出发，向后遍历搜索统计（考虑到之前的字符串都被统计搜索过，因此无需再进行搜索，提高效率）
* 设置visit数组，记录当前点开始的N长字符串是否被搜索记录过了；如果被记录过直接跳过；否则进行搜索统计

----
### **最后还是有一个case因为超时没过**