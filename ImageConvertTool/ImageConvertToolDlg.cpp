
// ImageConvertToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageConvertTool.h"
#include "ImageConvertToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageConvertToolDlg dialog




CImageConvertToolDlg::CImageConvertToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageConvertToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageConvertToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageConvertToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BT_INPUT, &CImageConvertToolDlg::OnBnClickedInput)
	ON_BN_CLICKED(BT_OUTPUT, &CImageConvertToolDlg::OnBnClickedOutput)
	ON_BN_CLICKED(BT_CONVERT, &CImageConvertToolDlg::OnBnClickedConvert)
	ON_BN_CLICKED(CK_RAWDATA, &CImageConvertToolDlg::OnBnClickedRawdata)
END_MESSAGE_MAP()


// CImageConvertToolDlg message handlers

BOOL CImageConvertToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if (!m_TB_Input.SubclassDlgItem(TB_INPUT, this)) return FALSE;
	if (!m_TB_Output.SubclassDlgItem(TB_OUTPUT, this)) return FALSE;
	if (!m_CK_RawData.SubclassDlgItem(CK_RAWDATA, this)) return FALSE;
	if (!m_CB_Input.SubclassDlgItem(CB_INPUT, this)) return FALSE;
	if (!m_LB_Resolution.SubclassDlgItem(LB_RESOLUTION, this)) return FALSE;
	if (!m_LB_X.SubclassDlgItem(LB_X, this)) return FALSE;
	if (!m_LB_BPP.SubclassDlgItem(LB_BPP, this)) return FALSE;
	if (!m_TB_Inx.SubclassDlgItem(TB_INX, this)) return FALSE;
	if (!m_TB_Iny.SubclassDlgItem(TB_INY, this)) return FALSE;
	if (!m_TB_BPP.SubclassDlgItem(TB_BPP, this)) return FALSE;
	if (!m_PG_Convert.SubclassDlgItem(PG_CONVERT, this)) return FALSE;

	m_CK_Formats = new CButton[ARRAY_SIZE(nFormats)];
	for (int i=0; i<ARRAY_SIZE(nFormats); i++) {
		m_CB_Input.AddString(sFormats[i]);
		if (!m_CK_Formats[i].SubclassDlgItem(nFormats[i], this)) return FALSE;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageConvertToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageConvertToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImageConvertToolDlg::OnBnClickedInput()
{
	OPENFILENAME ofn;

	memset(&ofn, 0, sizeof(ofn));
	m_szSrcFile[0] = 0;
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER;
	ofn.hwndOwner = this->GetSafeHwnd();
	ofn.lpstrFilter = _T("Any File\0*.*\0\0");
	ofn.lpstrFile = m_szSrcFile;
	GetOpenFileName(&ofn);
	if (_tcslen(m_szSrcFile)!=0) {
		m_TB_Input.SetWindowText(m_szSrcFile);
		_tcscpy_s(m_szDstFile, MAX_PATH, m_szSrcFile);
		int i;
		for (i=_tcslen(m_szDstFile)-1; i>=0; i--)
			if (m_szDstFile[i] == '.') break;
		if (i>=0) m_szDstFile[i] = 0;
		/*if (m_szDstFile[_tcslen(m_szDstFile)-4] == '.')
			_tcscpy_s(&m_szDstFile[_tcslen(m_szDstFile)-3], MAX_PATH, _T("bmp"));
		else
			_tcscat_s(m_szDstFile, MAX_PATH, _T(".bmp"));*/
		m_TB_Output.SetWindowText(m_szDstFile);
	}
}


void CImageConvertToolDlg::OnBnClickedOutput()
{
	OPENFILENAME ofn;

	memset(&ofn, 0, sizeof(ofn));
	m_szDstFile[0] = 0;
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER|OFN_OVERWRITEPROMPT;
	ofn.hwndOwner = this->GetSafeHwnd();
	ofn.lpstrFilter = _T("Bitmap(*.bmp)\0*.bmp\0\0");
	ofn.lpstrFile = m_szDstFile;
	ofn.lpstrDefExt = _T("bmp");
	GetSaveFileName(&ofn);
	if (_tcslen(m_szSrcFile)!=0) m_TB_Output.SetWindowText(m_szDstFile);
}


void CImageConvertToolDlg::OnBnClickedConvert()
{
	unsigned char *inBuf = NULL;

	m_TB_Input.GetWindowText(m_szSrcFile, MAX_PATH);
	m_TB_Output.GetWindowText(m_szDstFile, MAX_PATH);
	if (m_CK_RawData.GetCheck()) {
		TCHAR szX[16], szY[16], szBPP[16];
		m_TB_Inx.GetWindowText(szX, 16);
		m_TB_Iny.GetWindowText(szY, 16);
		m_TB_BPP.GetWindowText(szBPP, 16);
		m_x = _ttoi(szX);
		m_y = _ttoi(szY);
		m_bpp = _ttoi(szBPP);
	}

	m_inputSize = ReadInput(m_szSrcFile, &inBuf);
	if (!m_inputSize) {
		MessageBox(_T("Read input failed!"));
		return;
	}
	if (!m_CK_RawData.GetCheck() && m_CB_Input.GetCurSel() < MAX_BMP_TYPES) {
		inBuf = CheckHeader(inBuf);
		if (!inBuf) {
			MessageBox(_T("Check header failed!"));
			return;
		}
	}
	if (Convert(inBuf)) {
		MessageBox(_T("Convert failed!"));
		return;
	}
}


void CImageConvertToolDlg::OnBnClickedRawdata()
{
	if (m_CK_RawData.GetCheck()) {
		m_LB_Resolution.ShowWindow(SW_SHOW);
		m_LB_X.ShowWindow(SW_SHOW);
		m_LB_BPP.ShowWindow(SW_SHOW);
		m_TB_Inx.ShowWindow(SW_SHOW);
		m_TB_Iny.ShowWindow(SW_SHOW);
		m_TB_BPP.ShowWindow(SW_SHOW);
	} else {
		m_LB_Resolution.ShowWindow(SW_HIDE);
		m_LB_X.ShowWindow(SW_HIDE);
		m_LB_BPP.ShowWindow(SW_HIDE);
		m_TB_Inx.ShowWindow(SW_HIDE);
		m_TB_Iny.ShowWindow(SW_HIDE);
		m_TB_BPP.ShowWindow(SW_HIDE);
	}
}


int CImageConvertToolDlg::ReadInput(TCHAR *path, unsigned char **buf)
{
	FILE *fpbmp;
	unsigned int size;

	_tfopen_s(&fpbmp, path, _T("rb"));
	if (fpbmp == NULL) {
		MessageBox(_T("Open src file failed"));
		return 0;
	}

	fseek(fpbmp, 0, SEEK_END);
	size = ftell(fpbmp);
	fseek(fpbmp, 0, SEEK_SET);
	*buf = (unsigned char*)malloc(sizeof(unsigned char)*(size));
	if (!(*buf)) {
		MessageBox(_T("Alloc memory for src file failed"));
		return 0;
	}
	
	fread(*buf, size, 1, fpbmp);
	fclose(fpbmp);
	return size;
}

unsigned char* CImageConvertToolDlg::CheckHeader(unsigned char *buf)
{
	bmp_header *header = (bmp_header*)buf;
	if (header->magic_number != 0x4D42) return buf;

	dib_header *dib = (dib_header*)(buf+sizeof(bmp_header));
	m_x = dib->bitmap_width;
	m_y = dib->bitmap_height;
	m_bpp = dib->bits_per_pixel;
	m_inputSize -= header->offset;

	return &buf[header->offset];
}

int CImageConvertToolDlg::Convert(unsigned char *inBuf)
{
	funcToStandard tos;
	funcFromStandard froms;
	funcOutput fout;
	unsigned char *standBuf = NULL, *outBuf = NULL;
	unsigned int standSize, outSize;
	TCHAR outPath[MAX_PATH];
	int steps = 1;

	for (int i=0; i<ARRAY_SIZE(nFormats); i++)
		if (m_CK_Formats[i].GetCheck()) steps += 2;
	m_PG_Convert.SetRange(0, steps);
	m_PG_Convert.SetStep(1);
	m_PG_Convert.SetPos(0);

	standBuf = (unsigned char*)malloc(sizeof(char)*m_x*m_y*4);
	outBuf = (unsigned char*)malloc(sizeof(char)*m_x*m_y*4);
	memset(standBuf, 0, sizeof(char)*m_x*m_y*4);

	tos = ftoFormats[m_CB_Input.GetCurSel()];
	standSize = tos(inBuf, m_inputSize, m_x, m_y, standBuf);
	if (!standSize) {
		MessageBox(_T("Convert to standard format failed"));
		return -1;
	}
	m_PG_Convert.StepIt();
	for (int i=0; i<ARRAY_SIZE(nFormats); i++) {
		if (m_CK_Formats[i].GetCheck()) {
			memset(outBuf, 0, sizeof(char)*m_x*m_y*4);
			froms = ffromFormats[i];
			outSize = froms(standBuf, standSize, m_x, m_y, outBuf);
			if (!outSize) {
				TCHAR msg[256];
				_stprintf_s(msg, 256, _T("Convert to %s format failed"), sFormats[i]);
				MessageBox(msg);
				continue;
			}
			m_PG_Convert.StepIt();
			_stprintf_s(outPath, MAX_PATH, _T("%s_%s.%s"),
				m_szDstFile, sFormats[i],
				(i<MAX_BMP_TYPES)?_T("bmp"):_T("yuv"));
			fout = foutFormats[i];
			if (fout(outBuf, m_x, m_y, outPath)) {
				TCHAR msg[256];
				_stprintf_s(msg, 256, _T("Write output for %s failed"), sFormats[i]);
				MessageBox(msg);
			}
			m_PG_Convert.StepIt();
		}
	}
	if (standBuf != inBuf) free(standBuf);
	if (outBuf != standBuf) free(outBuf);
	return 0;
}

int CImageConvertToolDlg::WriteOutput(unsigned char *buf, unsigned int size, TCHAR *path)
{
	return 0;
}