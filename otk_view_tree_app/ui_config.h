#pragma once

/*--------------------------------------------------------------------------*\
|
|  Module Details:
|
|  Name:    ui_config.cxx
|
|  Purpose: Display the ui_config dialog
\*--------------------------------------------------------------------------*/

#include <uifcDefaultListeners.h>
#include <ProToolkit.h>


/*
** Component identifiers
*/

static char *UI_CONFIG_DIALOG = "ui_config";
static char *UI_CONFIG_CHECKBUTTON1 = "CheckButton1";
static char *UI_CONFIG_INPUTPANEL1 = "InputPanel1";
static char *UI_CONFIG_COMMITOK = "CommitOK";
static char *UI_CONFIG_COMMITCANCEL = "CommitCancel";


/*
** Function prototypes
*/

ProError ui_config_main(
	void
);



/*
** Action listeners
*/

class ui_configDialogListener : public uifcDefaultDialogListener
{
public:
	ui_configDialogListener() {}
	~ui_configDialogListener() {}

	void OnClose(uifcDialog_ptr handle);

};


class CheckButton1CheckButtonListener : public uifcDefaultCheckButtonListener
{
public:
	CheckButton1CheckButtonListener() {}
	~CheckButton1CheckButtonListener() {}

	void OnActivate(uifcCheckButton_ptr handle);
};


class InputPanel1InputPanelListener : public uifcDefaultInputPanelListener
{
public:
	InputPanel1InputPanelListener() {}
	~InputPanel1InputPanelListener() {}

	void OnActivate(uifcInputPanel_ptr handle);
};


class CommitOKPushButtonListener : public uifcDefaultPushButtonListener
{
public:
	CommitOKPushButtonListener() {}
	~CommitOKPushButtonListener() {}

	void OnActivate(uifcPushButton_ptr handle);
};


class CommitCancelPushButtonListener : public uifcDefaultPushButtonListener
{
public:
	CommitCancelPushButtonListener() {}
	~CommitCancelPushButtonListener() {}

	void OnActivate(uifcPushButton_ptr handle);
};

void GetSettinds();

