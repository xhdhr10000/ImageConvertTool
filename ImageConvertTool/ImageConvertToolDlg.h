
// ImageConvertToolDlg.h : header file
//

#pragma once

#include "Converter.h"

#define ARRAY_SIZE(X)	(sizeof(X)/sizeof(X[0]))
#define MAX_BMP_TYPES	10

const UINT nFormats[] = {
	CK_RGB888, CK_ARGB4444, CK_ARGB8888, CK_ABGR8888,
	CK_XRGB8888, CK_XBGR8888, CK_ABGR1555, CK_RGBA5551,
	CK_RGB565, CK_BGR565, CK_YUV420, CK_TILEMODE
};
const TCHAR sFormats[][16] = {
	_T("RGB888"), _T("ARGB4444"), _T("ARGB8888"), _T("ABGR8888"),
	_T("XRGB8888"), _T("XBGR8888"), _T("ABGR1555"), _T("RGBA5551"),
	_T("RGB565"), _T("BGR565"), _T("YUV420"), _T("TILEMODE")
};
const funcToStandard ftoFormats[] = {
	RGB888_to_standard, ARGB4444_to_standard,
	ARGB8888_to_standard, ABGR8888_to_standard,
	XRGB8888_to_standard, XBGR8888_to_standard,
	ABGR1555_to_standard, RGBA5551_to_standard,
	RGB565_to_standard, BGR565_to_standard,
	YUV420_to_standard, TILEMODE_to_standard
};
const funcFromStandard ffromFormats[] = {
	standard_to_RGB888, standard_to_ARGB4444,
	standard_to_ARGB8888, standard_to_ABGR8888,
	standard_to_XRGB8888, standard_to_XBGR8888,
	standard_to_ABGR1555, standard_to_RGBA5551,
	standard_to_RGB565, standard_to_BGR565,
	standard_to_YUV420, standard_to_TILEMODE
};
const funcOutput foutFormats[] = {
	output_RGB888, output_ARGB4444,
	output_ARGB8888, output_ABGR8888,
	output_XRGB8888, output_XBGR8888,
	output_ABGR1555, output_RGBA5551,
	output_RGB565, output_BGR565,
	output_YUV420, output_TILEMODE
};


// CImageConvertToolDlg dialog
class CImageConvertToolDlg : public CDialogEx
{
// Construction
public:
	CImageConvertToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_IMAGECONVERTTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON			m_hIcon;
	CEdit			m_TB_Input, m_TB_Output;
	CComboBox		m_CB_Input;
	CButton			m_CK_RawData, m_CK_OutRawData;
	CStatic			m_LB_Resolution, m_LB_X, m_LB_BPP;
	CEdit			m_TB_Inx, m_TB_Iny, m_TB_BPP;
	CButton			*m_CK_Formats;
	CProgressCtrl	m_PG_Convert;
	TCHAR			m_szSrcFile[MAX_PATH], m_szDstFile[MAX_PATH];

	UINT			m_x, m_y, m_bpp;
	UINT			m_inputSize;

	// Functions
	int ReadInput(TCHAR *path, unsigned char **buf);
	unsigned char* CheckHeader(unsigned char *buf);
	int Convert(unsigned char *inBuf);
	int WriteOutput(unsigned char *buf, unsigned int size, TCHAR *path);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInput();
	afx_msg void OnBnClickedOutput();
	afx_msg void OnBnClickedConvert();
	afx_msg void OnBnClickedRawdata();
};
