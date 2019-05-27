#include "./rapidjson/document.h"
#include "./rapidjson/writer.h"
#include "./rapidjson/stringbuffer.h"
#include <stdio.h>
#include <string>
int countArr[2] = { 123, 456 };
int numArr[2] = { 12, 32 };

const char* jsonStr = "{\"hello\":\"world\", \"t\" : true, \"f\" : false, \"n\" : null, \"i\" : 123, \"pi\" : 3.1416, \"arr\": [1, 2, 3, 4] }";
void Parse()
{
	// 每个 JSON 值都储存为 Value 类
	// RapidJSON 的所有公开类型及函数都在 rapidjson 命名空间中。
	rapidjson::Document document;	// Document 类则表示整个 DOM，它存储了一个 DOM 树的根 Value
	document.Parse(jsonStr);		// 解析json格式字符串
	
	// 查询一下根 Object 中有没有 "hello" 成员。由于一个 Value 可包含不同类型的值，我们可能需要验证它的类型，并使用合适的 API 去获取其值。在此例中，"hello" 成员关联到一个 JSON String。
	// assert(document.HasMember("hello"));	// 是否存在hello成员
	// assert(document["hello"].IsString());	// 判断是否是字符串
	printf("hello : %s\n",document["hello"].GetString());// 获取值
	
	// JSON True/False 值是以 bool 表示的
	// assert(document.HasMember("t"));
	// assert(document["t"].IsBool());	
	 printf("t : %d\n",document["t"].GetBool());// 获取值
	
	 // JSON Null 值可用 IsNull() 查询
	 // assert(document.HasMember("n"));
	 // assert(document["n"].IsNull());
	 
	 // JSON Number 类型表示所有数值。然而，C++ 需要使用更专门的类型。
	 // assert(document["i"].IsNumber());
	 // 在此情况下，IsUint()/IsInt64()/IsUInt64() 也会返回 true
	 // assert(document["i"].IsInt());
	 printf("i : %d\n",document["i"].GetInt());// 获取值
	 // 另一种用法： (int)document["i"]
	 // assert(document["pi"].IsNumber());
	 // assert(document["pi"].IsDouble());
	 printf("pi : %lf\n",document["pi"].GetDouble());// 获取值
	 // JSON Array 包含一些元素。
	 // 使用引用来连续访问，方便之余还更高效。
	 const rapidjson::Value& arr = document["arr"];
	 // assert(arr.IsArray());
	 for (rapidjson::SizeType i = 0; i < arr.Size(); i++) // 使用 SizeType 而不是 size_t,缺省情况下，SizeType 是 unsigned 的 typedef。在多数系统中，Array 最多能存储 2^32-1 个元素。
	 	printf("arr[%d] : %d\n",i,arr[i].GetInt());// 获取值
	 for (rapidjson::Value::ConstValueIterator itr = arr.Begin(); itr != arr.End(); ++itr)
		printf("arr[%d] : %d\n",itr - arr.Begin(),itr->GetInt());// 获取值
}

void Create()
{
	// 默认构造函数创建一个 Value 或 Document，它的类型便会是 Null。要改变其类型，需调用 SetXXX() 或赋值操作，
	rapidjson::Document document1;
	document1.SetObject();

	rapidjson::Value v;//NULL
	v.SetInt(10);// v = 10; 简写

	//构造函数的各个重载
	//几个类型也有重载构造函数：
	rapidjson::Value b1(true);    // 调用 Value(bool)
	rapidjson::Value i1(-123);    // 调用 Value(int)
	rapidjson::Value u1(123u);    // 调用 Value(unsigned)
	rapidjson::Value d1(1.5);     // 调用 Value(double)


	// 要重建空 Object 或 Array，可在默认构造函数后使用 SetObject() / SetArray()，或一次性使用 Value(Type)：
	rapidjson::Value a(rapidjson::kObjectType);
	rapidjson::Value b(rapidjson::kArrayType);

	// 转移语义(Move Semantics)
	rapidjson::Value c(123);
	rapidjson::Value d(456);
	d = c;         // c 变成 Null，d 变成数字 123。


	rapidjson::Document document2;
	rapidjson::Value author;
	char buffer1[10];
	int len = sprintf(buffer1, "%s %s", "Milo", "Yip"); // 动态创建的字符串。
	author.SetString(buffer1, len, document2.GetAllocator());
	memset(buffer1, 0, sizeof(buffer1));
	printf("%s\n",author.GetString());
	// 清空 buffer 后 author.GetString() 仍然包含 "Milo Yip"




	printf("1111111111111111111111111111111111111111111111111111111111111111111111\n");

	rapidjson::Document::AllocatorType& allocator = document1.GetAllocator();
	rapidjson::Value root(rapidjson::kObjectType);
	document1.AddMember("id", 1, allocator);
	document1.AddMember("num", 2, allocator);


	rapidjson::Value count(rapidjson::kArrayType);
	rapidjson::Value num(rapidjson::kArrayType);
	for (int i = 0; i <= 1; i++)
	{
		count.PushBack(countArr[i], allocator);   // 可能需要调用 realloc() 所以需要 allocator
		num.PushBack(numArr[i], allocator);   // 可能需要调用 realloc() 所以需要 allocator
	}

	document1.AddMember("count", count, allocator);
	document1.AddMember("num", num, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document1.Accept(writer);
	printf("%s\n",buffer.GetString());
	printf("1111111111111111111111111111111111111111111111111111111111111111111111\n");


	rapidjson::Document::AllocatorType& allocator2 = document2.GetAllocator();
	rapidjson::Value root2(rapidjson::kObjectType);
	root2.AddMember("id", 1, allocator2);
	root2.AddMember("n", 2, allocator2);


	rapidjson::Value count1(rapidjson::kArrayType);
	rapidjson::Value num1(rapidjson::kArrayType);
	for (int i = 0; i <= 1; i++)
	{
		count1.PushBack(countArr[i], allocator2);   // 可能需要调用 realloc() 所以需要 allocator2
		num1.PushBack(numArr[i], allocator2);   // 可能需要调用 realloc() 所以需要 allocator2
	}

	root2.AddMember("count", count1, allocator2);
	root2.AddMember("num", num1, allocator2);


	rapidjson::StringBuffer buffer2;
	rapidjson::Writer<rapidjson::StringBuffer> writer2(buffer2);
	root2.Accept(writer2);
	printf("%s\n",buffer2.GetString());
}
int main()
{

	rapidjson::Document document;
	document.Parse(jsonStr);
	printf("%d\n",document.HasMember("hello"));

	Parse();
	Create();
	return 0;
}
