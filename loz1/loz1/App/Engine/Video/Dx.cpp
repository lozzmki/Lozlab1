#include "Dx.h"
#include "..\..\Utilities\Common.h"
#include "..\..\App.h"
#include<d3d9.h>
#include<d3dx9.h>
#include"Sprite\Sprite.h"

D3D* g_d3d=0;

DWORD Vertex::FVF = D3DFVF_XYZ /*| D3DFVF_NORMAL*/ /*| D3DFVF_DIFFUSE*/ | D3DFVF_TEX1;

Vertex::Vertex(float x, float y, float z, float u, float v):_x(x), _y(y), _z(z), _u(u), _v(v){
	//_nx=0.0f; _ny=0.0f; _nz=-1.0f;
	//_color=0xffffffff;
}


D3D::D3D(){

}

D3D::~D3D(){

}

bool D3D::OnInit(){
	//#1 
	IDirect3D9* p_d3d9;
	p_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if(!p_d3d9){
		::MessageBox(0, _T("#1 p_d3d9 error"), 0, 0);
		return false;
	}


	//�ⶫ��������Կ������ܲ���
	D3DCAPS9 caps;
	p_d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		//Ӳ����������
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}else{
		//���
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	//#2

	//d3d����Ļ������Խṹ��
	D3DPRESENT_PARAMETERS dpp;

	//��̨������
	RECT _re;
	/*��ȡ�ͻ�����������������λ����*/
	GetClientRect(g_App->GetWnd(), &_re);
	dpp.BackBufferWidth = _re.right - _re.left;
	dpp.BackBufferHeight = _re.bottom - _re.top;

	//��̨�������ظ�ʽ
	dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//��̨�������
	dpp.BackBufferCount = 1;

	//���ز������ͺ��������ƺ�Ӱ��ȥ���
	dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	dpp.MultiSampleQuality = 0;

	//���彻�����ԣ�ָ��˫�����ǰ�󻺳彻����ʽ��DiscardΪ��ϵͳ�Զ�������Ч�����
	dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//���豸�����Ĵ��ھ��������Ҫ���ƵĴ��ڡ�
	dpp.hDeviceWindow = g_App->GetWnd();

	//����orȫ��
	dpp.Windowed = true;

	//�Զ�������ά����Ȼ����ģ�建�棬����true��
	dpp.EnableAutoDepthStencil = true;

	//��Ȼ����ģ�建������ظ�ʽ��D3DFMT_D24S8=��24λ��ʾ��ȣ�8λ������ģ�建��ʹ��
	dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	//�������ԣ����ã�D3DPRESENTFLAG_LOCKABLE_DEPTHBUFFER����������̨���棬�ή�����ܣ� D3DPRESENTFLAG_DISCARD_DEPTHBUFFER����һ����̨�����ύʱ���Ǹ���Ȼ�ģ�建�潫��������
	dpp.Flags = 0;

	//ˢ��Ƶ��
	dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	//��ʾʱ������Ĭ��ΪDEFAULT����D3D��ѡ���ύƵ�ʣ�һ��Ϊˢ��Ƶ�ʣ���IMMEDIATEΪ�����ύ��
	dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;




	//�����豸
	//IDirect3DDevice9* p_device = 0;

	HRESULT hr = p_d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL/*HALӲ����SW�����REF���ã�DEBUG�����RELEASEӲ����*/, g_App->GetWnd(), vp/*vertex processing*/, &dpp, &m_pDevice);

	if (FAILED(hr)){
		::MessageBox(0, _T("#2 CreateDevice error"), 0, 0);
		return false;
	}

	//���������豸
	 

	//��Ⱦģʽ���ӽǵȵ�����

	//g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);//��Ⱦ����ģʽ
	//g_Device->SetRenderState(D3DRS_LIGHTING, FALSE);//�رչ���
	/*
		D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMATRIX V;
		D3DXMatrixLookAtLH(&V, &position, &target, &up);//��position����target���ӽ�
		g_Device->SetTransform(D3DTS_VIEW, &V);
		

	
	*/
	D3DXMATRIX* Identity = new D3DXMATRIX;
	D3DXMatrixIdentity(Identity);
	g_Device->SetTransform(D3DTS_WORLD,
		Identity);
    g_Device->SetTransform(D3DTS_VIEW, Identity);
	D3DXMATRIX proj;
	D3DXMatrixOrthoLH(&proj, 400, 300, 0.0f, 1.0f);
		/*(
			&proj,
			D3DX_PI *0.8f,
			800.0f / 600.0f,
			1.0f,
			1000.0f);*/
	g_Device->SetTransform(D3DTS_PROJECTION, &proj);
	
	//lights
	/*
	D3DLIGHT9 _light;

	_light.Type=D3DLIGHT_DIRECTIONAL;
	_light.Ambient = D3DXCOLOR(0.4f,0.4f,0.4f,0.4f);
	_light.Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	_light.Specular = D3DXCOLOR(0.6f,0.6f,0.6f,0.6f);
	_light.Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	g_Device->SetLight(0, &_light);
	g_Device->LightEnable(0, true);
	*/
	g_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	g_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
	
	//g_Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//g_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	
	//g_Device->LightEnable(0, FALSE);
	g_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	D3DXFONT_DESC df;
	::ZeroMemory(&df, sizeof(D3DXFONT_DESC));
	df.Height = 25;
	df.Width = 10;
	df.Weight = 400;
	df.MipLevels = D3DX_DEFAULT;
	df.Italic = false;
	df.CharSet = DEFAULT_CHARSET;
	df.OutputPrecision = 0;
	df.Quality = 0;
	df.PitchAndFamily = 0;
	wcscpy(df.FaceName, _T("Times New Roman"));
	D3DXCreateFontIndirect(g_Device, &df, &m_pFont);

	//texturebase
	g_TexBase = new TextureBase();
	g_TexBase->PreloadTexture("test",L"..\\datafiles\\1-1.png");

	return true;
}


void D3D::StartRender(){
	
	if(g_Device){
		g_Device->Clear(0,0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		g_Device->BeginScene();
		g_Device->SetFVF(Vertex::FVF);
	}

}


void D3D::EndAndPresent(){

	if(g_Device){
		g_Device->EndScene();
		g_Device->Present(0,0,0,0);//present backbuffer
	}
}

void D3D::testrender(float timeDelta){

	static Sprite* sprite = new Sprite();

	sprite->setTexture(_TEXNODE("test"));

	static double time = 0.0;

	time+=timeDelta;
	if(time>6.28)time-=6.28;

	double x=100.0*cos(time)+200.0;
	double y=100.0*sin(time)+200.0;

	sprite->setPos(x, y);
	sprite->setScale(sin(time), 1.0);
	sprite->setRotate(time);

	sprite->render();
}