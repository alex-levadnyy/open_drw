#include "ui_config.h"
#include "rw_file.h"

#include <ProUIDialog.h>
#include <uifcDialog.h>

/*
** ui_config main function
*/

/*--------------------------------------------------------------------------*\
| Function: ui_config_main
| Purpose:  Create the Dialog ui_config, setup the actions on the dialog
|           and then place the dialog on the screen
| Input:
| Output:
| Return:   PRO_TK_NO_ERROR if everything went well, otherwise an error code
\*--------------------------------------------------------------------------*/
ProError ui_config_main (void)
{
	Settings settings = LoadSettings();
	xint status;

  if ((status = uifcCreateDialog (UI_CONFIG_DIALOG, UI_CONFIG_DIALOG)) == 0)
  {
    uifcDialog_ptr ui_config = uifcDialogFind(UI_CONFIG_DIALOG, UI_CONFIG_DIALOG);
	ui_configDialogListener *ui_configLis = new ui_configDialogListener();
    ui_config->AddActionListener(ui_configLis);
    
    uifcCheckButton_ptr checkbutton1 = uifcCheckButtonFind(UI_CONFIG_DIALOG, UI_CONFIG_CHECKBUTTON1);
	CheckButton1CheckButtonListener *checkbutton1Lis = new CheckButton1CheckButtonListener();
    checkbutton1->AddActionListener(checkbutton1Lis);
	uifcCheckState value_check;
	{
		settings.subdir == true ? value_check = uifcCHECK_STATE_SET : value_check = uifcCHECK_STATE_UNSET;
	}
	checkbutton1->SetCheckedState(value_check);
    
    uifcInputPanel_ptr inputpanel1 = uifcInputPanelFind(UI_CONFIG_DIALOG, UI_CONFIG_INPUTPANEL1);
	InputPanel1InputPanelListener *inputpanel1Lis = new InputPanel1InputPanelListener();	
    inputpanel1->AddActionListener(inputpanel1Lis);
	inputpanel1->SetTextValue(settings.suff_sp);
	
	
	uifcPushButton_ptr commitok = uifcPushButtonFind(UI_CONFIG_DIALOG, UI_CONFIG_COMMITOK);
	CommitOKPushButtonListener *commitokLis = new CommitOKPushButtonListener();
    commitok->AddActionListener(commitokLis);
    
    uifcPushButton_ptr commitcancel = uifcPushButtonFind(UI_CONFIG_DIALOG, UI_CONFIG_COMMITCANCEL);
	CommitCancelPushButtonListener *commitcancelLis = new CommitCancelPushButtonListener();
    commitcancel->AddActionListener(commitcancelLis);
    
    status = uifcActivateDialog (UI_CONFIG_DIALOG);


    if (status == 0)
      status = uifcDestroyDialog (UI_CONFIG_DIALOG);

    delete ui_configLis;
    delete checkbutton1Lis;
    delete inputpanel1Lis;
    delete commitokLis;
    delete commitcancelLis;
  }

  return (status == 0 ? PRO_TK_NO_ERROR: PRO_TK_GENERAL_ERROR);
}

void GetSettinds()
{
	uifcCheckButton_ptr checkbutton1 = uifcCheckButtonFind(UI_CONFIG_DIALOG, UI_CONFIG_CHECKBUTTON1);
	uifcInputPanel_ptr inputpanel1 = uifcInputPanelFind(UI_CONFIG_DIALOG, UI_CONFIG_INPUTPANEL1);
	bool recursive_search;
	checkbutton1->GetCheckedState() == uifcCHECK_STATE_SET ? recursive_search = true : recursive_search = false;
	xstring syffic = inputpanel1->GetTextValue();
	SaveSettings(recursive_search, syffic);

}


/*
** Action functions
*/

/*--------------------------------------------------------------------------*\
| Function: ui_configDialogListener::OnClose
| Purpose:  Close action has occured for Dialog ui_config
| Input:    handle         - handle to Dialog component
| Output:
| Return:
\*--------------------------------------------------------------------------*/
void ui_configDialogListener::OnClose(uifcDialog_ptr handle)
{
  uifcExitDialog (UI_CONFIG_DIALOG, 0);
}


/*--------------------------------------------------------------------------*\
| Function: CheckButton1CheckButtonListener::OnActivate
| Purpose:  Activate action has occured for CheckButton CheckButton1
| Input:    handle         - handle to CheckButton component
| Output:
| Return:
\*--------------------------------------------------------------------------*/
void CheckButton1CheckButtonListener::OnActivate(uifcCheckButton_ptr handle/*, Config_search* data*/)
{
}


/*--------------------------------------------------------------------------*\
| Function: InputPanel1InputPanelListener::OnActivate
| Purpose:  Activate action has occured for InputPanel InputPanel1
| Input:    handle         - handle to InputPanel component
| Output:
| Return:
\*--------------------------------------------------------------------------*/
void InputPanel1InputPanelListener::OnActivate(uifcInputPanel_ptr handle/*, Config_search* data*/)
{
}


/*--------------------------------------------------------------------------*\
| Function: CommitOKPushButtonListener::OnActivate
| Purpose:  Activate action has occured for PushButton CommitOK
| Input:    handle         - handle to PushButton component
| Output:
| Return:
\*--------------------------------------------------------------------------*/
void CommitOKPushButtonListener::OnActivate(uifcPushButton_ptr handle)
{
	GetSettinds();
}


/*--------------------------------------------------------------------------*\
| Function: CommitCancelPushButtonListener::OnActivate
| Purpose:  Activate action has occured for PushButton CommitCancel
| Input:    handle         - handle to PushButton component
| Output:
| Return:
\*--------------------------------------------------------------------------*/
void CommitCancelPushButtonListener::OnActivate(uifcPushButton_ptr handle)
{
	uifcExitDialog(UI_CONFIG_DIALOG, PRO_TK_NO_ERROR);
}

