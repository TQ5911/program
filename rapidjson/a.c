#include "./rapidjson/document.h"
#include "./rapidjson/writer.h"
#include "./rapidjson/stringbuffer.h"
#include <stdio.h>
const char* jsonStr = "{\"hello\":\"world\", \"t\" : \"true\", \"f\" : \"false\", \"n\" : \"null\", \"i\" : \"123\", \"pi\" : \"3.1416\", \"a \": \"[1, 2, 3, 4]\" }";

int main()
{
	rapidjson::Document document;
	document.Parse(jsonStr);
	printf("%d\n",document.HasMember("hello"));
	return 0;
}
