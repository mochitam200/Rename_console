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
	// コンソールの日本語表示・入力を正しく処理するためのロケール設定
	std::locale::global(std::locale("")); // ワイド文字列の標準出力（std::wcout）に現在の環境ロケールを適用（imbue）およびC++のグローバルなロケールをOSの現在の環境設定（日本語環境であれば Japanese など）に更新
	std::wcout.imbue(std::locale("")); // ワイド文字列の標準出力（std::wcout）に現在の環境ロケールを適用（imbue）
	std::wcin.imbue(std::locale("")); // ワイド文字列の標準入力（std::wcin）に環境ロケールを適用

	std::wcout << L"===ファイル一括リネームツール===\n\n";

	// 1.対象フォルダの設定
	fs::path targetDir;
	// path //	ファイルシステムライブラリが提供している「パス（ファイルやフォルダの場所）」を専門に扱うためのクラス
	while (true) {
		std::wcout << L"対象フォルダのパスを入力してください:";
		std::wstring input;
		std::getline(std::wcin,input);
		// std::getline() //		C++の標準ライブラリが提供する、「1行丸ごと読み込む」ための関数

		// エクスプローラー等からドラッグ&ドロップした際のダブルクォーテーションを除去
		{
			if (input.size() >= 2 && input.front() == L'"' && input.back() == L'"') {
				// input.size() >= 2 //文字列の長さ（文字数）が 2文字以上であるか をチェック
				// front() //文字列の先頭（1文字目）を指す関数,それが L'"'（ワイド文字のダブルクォーテーション）であるかを判定
				// back() は、文字列の末尾（最後の文字）を指す関数,それが L'"'（ワイド文字のダブルクォーテーション）であるかを判定
				
				input = input.substr(1, input.size() - 2);
				// input.substr(...)（サブストリング）//	文字列（std::wstring や std::string）の一部を切り取るための関数
				// 第1引数：1（開始位置）
				// 第2引数：input.size() - 2（切り取る文字数）先頭の1文字と、末尾の1文字の「計2文字分」を引いた長さを指定
			}

			targetDir = fs::path(input);
			// fs::path(input)（型変換 / コンストラクタの呼び出し）
			// std::wstring 型（ただの文字列）である input を、fs::path という「ファイルシステム専用の型」へと変換（キャスト）
		}

		//ディレクトリの存在確認
		if (fs::exists(targetDir) && fs::is_directory(targetDir)) {
			break;
		}
		std::wcout << L"[エラー]指定されたパスが存在しないか、ディレクトリではありません。再入力してください\n\m";
	}

	// 2.バックアップの作成


}