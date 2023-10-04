#pragma once

#include <string>

class CWaveGenDlg : public CDialogEx
{

public :
	CWaveGenDlg( CWnd * pParent = nullptr ) ;

#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_WAVEGEN_DIALOG
	} ;
#endif

protected :
	virtual void DoDataExchange( CDataExchange * pDX ) ;

	bool CheckInputs( double & freq , double & amp , double & phase ) const ;
	bool MakeWaveFile( std::string const & path , double const & freq , double const & amp ) ;

	bool WriteWaveOnMemory( double const & freq , double const & amp ) ;

protected :
	HICON m_hIcon ;

	virtual BOOL OnInitDialog() ;
	afx_msg void OnPaint() ;
	afx_msg HCURSOR OnQueryDragIcon() ; 
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGen() ;
	afx_msg void OnBnClickedButtonLowPlay() ;
} ;
