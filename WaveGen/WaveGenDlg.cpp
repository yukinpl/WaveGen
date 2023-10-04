#include "pch.h"
#include "framework.h"
#include "WaveGen.h"
#include "WaveGenDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <fstream>
#include <new>

#include "Wav.h"

#pragma comment( lib , "winmm" )
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CWaveGenDlg::CWaveGenDlg( CWnd * pParent /*=nullptr*/ )
	: CDialogEx( IDD_WAVEGEN_DIALOG , pParent )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME ) ;
}

void CWaveGenDlg::DoDataExchange( CDataExchange * pDX )
{
	CDialogEx::DoDataExchange( pDX ) ;
}

BEGIN_MESSAGE_MAP( CWaveGenDlg , CDialogEx )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED( IDC_BUTTON_GEN , &CWaveGenDlg::OnBnClickedButtonGen )
	ON_BN_CLICKED( IDC_BUTTON_LOW_PLAY , &CWaveGenDlg::OnBnClickedButtonLowPlay )
END_MESSAGE_MAP()




BOOL CWaveGenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog() ;

	SetIcon( m_hIcon , TRUE  ) ;
	SetIcon( m_hIcon , FALSE ) ;

	SetDlgItemTextW( IDC_EDIT_AMP  , _T( "3000.0" ) ) ;
	SetDlgItemTextW( IDC_EDIT_FREQ , _T( "440.0"  ) ) ;

	return TRUE ; 
}


void CWaveGenDlg::OnPaint()
{
	if( IsIconic() )
	{
		CPaintDC dc( this ) ;

		SendMessage( WM_ICONERASEBKGND , reinterpret_cast< WPARAM >( dc.GetSafeHdc() ) , 0 ) ;

		int cxIcon = GetSystemMetrics( SM_CXICON ) ;
		int cyIcon = GetSystemMetrics( SM_CYICON ) ;

		CRect rect ;
		GetClientRect( &rect ) ;
		int x = ( rect.Width()  - cxIcon + 1 ) / 2 ;
		int y = ( rect.Height() - cyIcon + 1 ) / 2 ;

		dc.DrawIcon( x , y , m_hIcon ) ;
	}
	else
	{
		CDialogEx::OnPaint() ;
	}
}


HCURSOR CWaveGenDlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon ) ;
}



void CWaveGenDlg::OnBnClickedButtonGen()
{
	double freq = 0.0 , amp = 0.0 , phase = 0.0 ;
	if( false == CheckInputs( freq , amp , phase ) )
	{
		return ;
	}

	std::string path = "daniel_wav_tmp.wav" ;
	if( false == MakeWaveFile( path , freq , amp ) )
	{
		return ;
	}

	PlaySound( _T( "daniel_wav_tmp.wav" ) , AfxGetInstanceHandle() , SND_ASYNC ) ;
}


bool CWaveGenDlg::CheckInputs( double & freq , double & amp , double & phase ) const
{
	CString tmp ;
	GetDlgItemTextW( IDC_EDIT_FREQ , tmp ) ;
	tmp = tmp.Trim() ;

	if( 0 >= tmp.GetLength() )
	{
		AfxMessageBox( _T( "Please input a frequency( Hz )" ) ) ;
		return false ;
	}

	freq = _ttof( tmp ) ;

	GetDlgItemTextW( IDC_EDIT_AMP , tmp ) ;
	tmp = tmp.Trim() ;

	if( 0 >= tmp.GetLength() )
	{
		AfxMessageBox( _T( "Please enter an amplitude" ) ) ;
		return false ;
	}

	amp = _ttof( tmp ) ;
/*
	if( 1000.0 > amp )
	{
		AfxMessageBox( _T( "Please enter an amplitude greater than 1000" ) ) ;
		return false ;
	}
*/
/*
	GetDlgItemTextW( IDC_EDIT_PHASE , tmp ) ;
	tmp = tmp.Trim() ;

	if( 0 >= tmp.GetLength() )
	{
		AfxMessageBox( _T( "Please enter a phase" ) ) ;
		return false ;
	}

	phase = _ttof( tmp ) ;
*/
	return true ;
}


bool CWaveGenDlg::MakeWaveFile( std::string const & path , double const & freq , double const & amp )
{
	std::ofstream ofs ;

	ofs.open( path , std::ios_base::out | std::ios_base::binary ) ;
	if( !ofs.is_open() )
	{
		return false ;
	}

	Wave::Wav wav ;

	uint16_t channel    =     1 ;
	uint32_t sampleRate = 44100 ;
	uint8_t  bitRate    =    32 ;
	uint8_t  duration   =     1 ;   // second
	uint32_t rawDataSize = duration * sampleRate * channel * bitRate / 8 ;

	wav.SetNumbersOfChannel( channel ) ;
	wav.SetSampleRate( sampleRate ) ;
	wav.SetByteRate( sampleRate * channel * bitRate / 8 ) ;
	wav.SetSizeOfSampleFrame( channel * bitRate / 8 ) ;
	wav.SetBitDepth( bitRate ) ;
	wav.SetRawDataSize( rawDataSize ) ;
	wav.Write( ofs ) ;


	constexpr float PI = 3.141592653589793238462643f ;

	for( uint32_t pos = 0 ; pos < rawDataSize ; ++pos )
	{
		uint16_t val = static_cast< uint16_t >( amp * sin( PI * pos * freq / sampleRate ) ) ;
		ofs.write( reinterpret_cast< char const * >( & val ) , 2 ) ;
	}

	ofs.close() ;

	return true ;
}


void CWaveGenDlg::OnBnClickedButtonLowPlay()
{
	double freq = 0.0 , amp = 0.0 , phase = 0.0 ;
	if( false == CheckInputs( freq , amp , phase ) )
	{
		return ;
	}

	if( false == WriteWaveOnMemory( freq , amp ) )
	{
		return ;
	}
}



#pragma warning( disable: 6262 ) 

void CALLBACK waveOutProc( HWAVEOUT hwo , UINT uMsg , DWORD_PTR dwInstance , DWORD_PTR dwParam1 , DWORD_PTR dwParam2 )
{
	AfxMessageBox( _T( "CALLBACK" ) ) ;
}


bool CWaveGenDlg::WriteWaveOnMemory( double const & freq , double const & amp )
{
	uint16_t channel = 1 ;
	uint32_t sampleRate = 44100 ;
	uint8_t  bitRate = 32 ;
	uint8_t  duration = 1 ;   // second
	uint32_t rawDataSize = duration * sampleRate * channel * bitRate / 8 ;

	WAVEFORMATEX pwfx ;
	pwfx.wFormatTag = WAVE_FORMAT_PCM ;
	pwfx.nChannels = channel ; // 1 - mono , 2 - stereo
	pwfx.nSamplesPerSec = sampleRate ; // 44.1 kHz
	pwfx.wBitsPerSample = bitRate ;
	pwfx.nBlockAlign = channel * bitRate / 8 ;
	pwfx.nAvgBytesPerSec = sampleRate * channel * bitRate / 8 ; // bit rate
	pwfx.cbSize = 0 ;

	/*
	 *  _Out_opt_ LPHWAVEOUT      phwo ,
	     _In_     UINT            uDeviceID ,
	     _In_     LPCWAVEFORMATEX pwfx ,
	     _In_opt_ DWORD_PTR       dwCallback ,
	     _In_opt_ DWORD_PTR       dwInstance ,
	     _In_     DWORD           fdwOpen
	 ) ;
	 */
	CString tmp ;
	UINT numbersOfDevice = waveOutGetNumDevs() ;
	if( !numbersOfDevice )
	{
		//AfxMessageBox( _T( "No device available" ) ) ;
		return false ;
	}

	MMRESULT res = waveOutOpen( 0 , WAVE_MAPPER , & pwfx , 0 , 0 , WAVE_FORMAT_QUERY ) ;
	if( res )
	{
		tmp.Format( _T( "In this system, the specified format is not supported. cause number:[ %d ]" ) , res ) ;

		//AfxMessageBox( tmp ) ;
		return false ;
	}

	HWAVEOUT outHandle ;
	HWND hwnd = GetSafeHwnd() ;
	res = waveOutOpen( & outHandle , WAVE_MAPPER , & pwfx , /*( DWORD_PTR ) waveOutProc */ 0 , ( DWORD_PTR ) & hwnd , CALLBACK_WINDOW ) ;
	if( res )
	{
		tmp.Format( _T( "Fail to open - waveOutOpen(). cause number:[ %d ]" ) , res ) ;
		//AfxMessageBox( tmp ) ;
		return false ;
	}

	constexpr float PI = 3.141592653589793238462643f ;

	uint16_t val[ 200000 ] ;
	for( uint32_t pos = 0 ; pos < rawDataSize ; ++pos )
	{
		val[ pos ] = static_cast< uint16_t >( amp * sin( PI * pos * freq / sampleRate ) ) ;
	}

	WAVEHDR outHeader ;

	memset( & outHeader , 0 , sizeof( outHeader ) ) ;
	outHeader.dwBufferLength = rawDataSize ;
	outHeader.lpData = ( LPSTR ) val ;
	outHeader.dwLoops = 0 ;
	outHeader.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP ;

	res = waveOutPrepareHeader( outHandle , & outHeader , sizeof( outHeader ) ) ;
	if( res )
	{
		tmp.Format( _T( "Fail to open - waveOutPrepareHeader(). cause number:[ %d ]" ) , res ) ;
		//AfxMessageBox( tmp ) ;
		return false ;
	}

	res = waveOutWrite( outHandle , & outHeader , sizeof( outHeader ) ) ;
	if( res )
	{
		tmp.Format( _T( "Fail to open - waveOutWrite(). cause number:[ %d ]" ) , res ) ;
		//AfxMessageBox( tmp ) ;
		return false ;
	}

	waveOutUnprepareHeader( outHandle , & outHeader , sizeof( outHeader ) ) ;
	waveOutClose( outHandle ) ;

	return true ;
}