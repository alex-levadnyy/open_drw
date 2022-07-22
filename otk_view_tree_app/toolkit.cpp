#include "ui_config.h"
#include "rw_file.h"

#include <fstream>
#include <stdio.h>
#include <wchar.h>
#include <vector>

/*-------------------------- Pro/Toolkit includes ---------------------------*/
#include <ProToolkit.h>
#include <ProMenu.h>
#include <ProMenuBar.h>
#include <ProUtil.h>

#include <pfcWindow.h>
#include <pfcSession.h>
#include <wfcSession.h>
#include <pfcGlobal.h>
#include <pfcExceptions.h>
#include <xstring.h>
#include <wfcGlobal.h>
#include <stdcols.h>
#include <pfcProToolkit.h>
#include <wfcAssembly.h>
#include <pfcModelItem.h>

#include <wfcDisplay.h>

/*-------------------------- Global variables ----------------------------*/
struct Data_for_open
{
	int file_version = 0;
	xstring dir_for_open=L"";
};

xstring suffic = ".drw";
xstring suffic_filter = "*" + suffic;


/*-------------------------- Function prototypes ----------------------------*/
extern "C" int open_drw();
extern "C" int open_drw_sp();
extern "C" int open_drw_base(bool isspec);
Data_for_open ParserPathandName(xstringsequence_ptr& files, xstring &dir, xstring &model_name);

/*-------------------------- Application defines ----------------------------*/
wchar_t *msgfil = L"message.txt";
static ofstream logFile;

extern "C" int user_initialize()
{
	ProError perr = PRO_TK_NO_ERROR;
	uiCmdCmdId cmd_id;

	/*button open_drw*/
	perr = ProCmdActionAdd("Toolkit_Issue",
		(uiCmdCmdActFn) open_drw,
		uiProeImmediate , NULL, PRO_B_TRUE,
		PRO_B_TRUE, &cmd_id);

	perr = ProCmdDesignate(cmd_id, "Toolkit Button", "Toolkit Button", "Toolkit Button", msgfil);

	perr = ProCmdIconSet (cmd_id, "sma.gif");

	perr = ProMenubarMenuAdd(
		"Toolkit Menu", "Toolkit Menu", "Help",
		PRO_B_TRUE, msgfil);
	perr = ProMenubarmenuPushbuttonAdd(
		"Toolkit Menu", "Toolkit Button",
		"Toolkit Button", "Toolkit Button",
		NULL, PRO_B_TRUE, cmd_id,
		msgfil);

	/*button open_drw_sp*/
	perr = ProCmdActionAdd("Toolkit_Issue2",
		(uiCmdCmdActFn)open_drw_sp,
		uiProeImmediate, NULL, PRO_B_TRUE,
		PRO_B_TRUE, &cmd_id);

	perr = ProCmdDesignate(cmd_id, "Toolkit Button1", "Toolkit Button1", "Toolkit Button1", msgfil);

	perr = ProCmdIconSet(cmd_id, "sma2.gif");

	perr = ProMenubarMenuAdd(
		"Toolkit Menu", "Toolkit Menu", "Help",
		PRO_B_TRUE, msgfil);
	perr = ProMenubarmenuPushbuttonAdd(
		"Toolkit Menu", "Toolkit Button1",
		"Toolkit Button1", "Toolkit Button1",
		NULL, PRO_B_TRUE, cmd_id,
		msgfil);

	/*button config*/
	perr = ProCmdActionAdd("Toolkit_Issue3",
		(uiCmdCmdActFn)ui_config_main,
		uiProeImmediate, NULL, PRO_B_TRUE,
		PRO_B_TRUE, &cmd_id);

	perr = ProCmdDesignate(cmd_id, "Toolkit Button2", "Toolkit Button2", "Toolkit Button2", msgfil);

	perr = ProCmdIconSet(cmd_id, "sma3.gif");

	perr = ProMenubarMenuAdd(
		"Toolkit Menu", "Toolkit Menu", "Help",
		PRO_B_TRUE, msgfil);
	perr = ProMenubarmenuPushbuttonAdd(
		"Toolkit Menu", "Toolkit Button2",
		"Toolkit Button2", "Toolkit Button2",
		NULL, PRO_B_TRUE, cmd_id,
		msgfil);	
	return (0);
}

/*------------ toolkit_issue ------------------------------------------------*/
/* function called when pressing user-defined button toolkit_issue           */
/*---------------------------------------------------------------------------*/

int open_drw_base(bool isspec)
{
	Data_for_open open;
	Settings settings = LoadSettings();

	try {
		pfcSession_ptr Session = pfcGetProESession();

		//show in graphics: 
		pfcModelDescriptor_ptr desc = NULL;

		pfcModel_ptr model = Session->GetCurrentModel();
		xstring dir = Session->GetCurrentDirectory();

		if (model != NULL) {
			xstring temp_name;
			xstring model_name = model->GetFullName();
			xstring generic_name = model->GetGenericName();

			// check the model is not an instance
			if (!generic_name.IsEmpty()) { 
				model_name = generic_name;
			}
			if (!isspec) {
				if (model_name.Match("*" + settings.suff_sp)) {
					temp_name = model_name.Substring(0, model_name.GetLength() - settings.suff_sp.GetLength());
				}
				else {
					temp_name = model_name;
				}
			}
			else {
				temp_name = model_name + settings.suff_sp.ToUpper();
			}

			//list file drw current dir
			xstringsequence_ptr files = Session->ListFiles(suffic_filter, pfcFILE_LIST_LATEST, dir);
			open = ParserPathandName(files, dir, temp_name);
			if (settings.subdir) {
				//list sudir
				xstringsequence_ptr subdir = Session->ListSubdirectories(dir);
				for (xint i = 0; i < subdir->getarraysize(); ++i) {
					xstringsequence_ptr temp_files = Session->ListFiles(suffic_filter, pfcFILE_LIST_LATEST, subdir->get(i));
					if (temp_files->getarraysize() > 0) {
						xstring tmp = subdir->get(i);
						Data_for_open temp_open = ParserPathandName(temp_files, tmp, temp_name);
						if (temp_open.file_version > open.file_version) {
							open.file_version = temp_open.file_version;
							open.dir_for_open = temp_open.dir_for_open;
						}
					}
				}
			}
			if (open.file_version != 0) {
				model_name = temp_name + suffic;
				try {
					Session->ChangeDirectory(open.dir_for_open);
					desc = pfcModelDescriptor::CreateFromFileName(model_name);
					Session->OpenFile(desc)->Activate();
				}
				xcatchbegin
					xcatch(pfcXInvalidFileName, xfn)

					return wfcTK_INVALID_FILE;
				xcatch(pfcXUnknownModelExtension, xume)

					return wfcTK_INVALID_FILE;
				xcatchend

					Session->ChangeDirectory(dir);
			}
			else {
				Session->UIDisplayLocalizedMessage("message.txt", "messageNorDRW", NULL);
			}
		}
	}

	xcatchbegin
		xcatchcip(Ex)
		xcatchend
	return 0;
}


extern "C" int open_drw ()
{
	return open_drw_base(false);
} 

extern "C" int open_drw_sp()
{
	return open_drw_base(true);
}

Data_for_open ParserPathandName(xstringsequence_ptr& files, xstring &dir, xstring &model_name)
{	
	Data_for_open result;
	xstring temp_file;
	result.dir_for_open = dir;
	
	xstring by_find = "*" + model_name.ToUpper() + suffic.ToUpper() + "*";

	for (xint i = 0; i < files->getarraysize(); ++i) {
		xstring path_to_search = files->get(i).ToUpper();
		if (path_to_search.Match(by_find)) {
			temp_file = files->get(i);
			temp_file = temp_file.Substring(dir.GetLength());
			temp_file.GetWord(2, ".").ToInt(&(result.file_version));
			break;
		}
	}
	return result;
}

extern "C" void user_terminate()
{

}
