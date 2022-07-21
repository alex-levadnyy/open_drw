#include "rw_file.h"
#include <iostream>


Settings LoadSettings()
{
	std::fstream file;
	vector<string> lines;
	std::string str;
	char x[500];
	Settings settings;
	wfcWSession_ptr ses;
	try {
		ses = wfcWSession::cast(pfcGetProESession());
	}
	xcatchbegin
		xcatchcip(Ex)
		xcatchend

	xstring path = ses->GetApplicationPath();
	path = path.Substring(0, (path.GetLength() - 3)); // 3 - size "dll"
	path += "txt";

	strcpy(x, path);
	file.open(x, ios_base::in);

	if (file.is_open()) {
		if (!(std::getline(file, str))) {
			return settings;
		}
		while (std::getline(file, str)) {
			lines.push_back(str);
		}
	}
	else { 
		return settings;
	}
	(lines.at(0) == "true") ? settings.subdir = true : settings.subdir = false;
	settings.suff_sp = lines.at(1).data();
	file.close();
	
	return settings;
}

void SaveSettings(bool recursive_search, xstring syffix)
{
	std::fstream file;
	wfcWSession_ptr ses;
	char x[500];
	try {
		ses = wfcWSession::cast(pfcGetProESession());
	}
	xcatchbegin
		xcatchcip(Ex)
		xcatchend

	if (syffix.IsEmpty()) {
		syffix = "empty";
	}	

	xstring path = ses->GetApplicationPath();
	path = path.Substring(0, (path.GetLength() - 3)); // 3 - size "dll"
	path += "txt";

	strcpy(x, path);
	file.open(x, ios_base::out | ios_base::trunc);

	if (file.is_open()) {
		file << std::boolalpha;
		file << "1" << std::endl
			<< recursive_search << std::endl
			<< syffix.ToUpper();
	}
	ses->UIDisplayLocalizedMessage("message.txt", "SettingsSaved", NULL);
}
