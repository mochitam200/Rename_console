#include<iostream>
#include<string>
#include<filesystem>
#include<vector>
#include<chrono>
#include<iomanip>
#include<sstream>
#include<algorithm>

// std::filesystemの名前空間のエイリアス(ファイル操作)
namespace fs = std::filesystem;

/*
@brief 現在時刻のタイムスタンプ文字列(YYYYMMDD_HHMMSS)を生成
@return std::wstring タイムスタンプ文字列
*/
std::wstring getTimestampString() {
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::tm timeBuf;

#if defined(_MSC_VER)
	// Windows用の安全なlocaltime
	localtime_s(&timeBuf, &in_time_t); (&timeBuf,&in_time_t);
#else
	// Unix/macOSの安全なlocaltaime
	localtaime_r(&in_time_t, &timeBuf);
#endif

	std::wstringstream wss;
	/*ストリーム出力機能を使って構造化された時刻（timeBuf）を
	「YYYYMMDD_HHMMSS」という形式の文字列に変換し、wss（std::ostringstreamなど）へ書き込む操作*/
	wss << std::put_time(&timeBuf, L"%Y%m%d_%H%M%S");
	return wss.str();	
}

/*
 * @brief 文字列内の特定の文字列をすべて置換します。
 * @param str 元の文字列
 * @param from 置換前の文字列
 * @param to 置換後の文字列
 * @return std::wstring 置換後の文字列
*/

std::wstring replaceAll(std::wstring str, const std::wstring from, const std::wstring to) {
	if (from.empty())return str;
	size_t start_pos = 0;
	/*文字列の中から特定の文字列をすべて検索し、ループ処理を繰り返すための定型句
	str.find(from, start_pos): str の中の start_pos の位置から、検索したい文字列 from を探す
	(start_pos = ...): 見つかった位置（インデックス）を start_pos という変数に代入
	!= std::wstring::npos: find の結果が
	「見つからなかったことを示す特殊な値（std::wstring::npos）」ではない（＝文字列が見つかった）間、ループを続る
	*/
		while ((start_pos = str.find(from, start_pos)) != std::wstring::npos) { 
		// start_pos の位置から、from.length()（検索した文字列の長さ）分だけ文字を切り取り、そこに新しい文字列 to を挿入
		str.replace(start_pos, from.length(), to);
		//次の検索を「今回置き換えた文字列 to の後ろ」から開始するために、検索開始位置（start_pos）を to.length() 分だけ進める
		start_pos += to.length();
	}
	return str;
}

int main() {

}