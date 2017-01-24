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


	//这东西存的是显卡的性能参数
	D3DCAPS9 caps;
	p_d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		//硬件顶点运算
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}else{
		//软件
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	//#2

	//d3d对象的绘制特性结构体
	D3DPRESENT_PARAMETERS dpp;

	//后台缓存宽高
	RECT _re;
	/*获取客户区宽高以修正点击错位问题*/
	GetClientRect(g_App->GetWnd(), &_re);
	dpp.BackBufferWidth = _re.right - _re.left;
	dpp.BackBufferHeight = _re.bottom - _re.top;

	//后台缓存像素格式
	dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//后台缓存个数
	dpp.BackBufferCount = 1;

	//多重采样类型和质量，似乎影响去锯齿
	dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	dpp.MultiSampleQuality = 0;

	//缓冲交换策略，指定双缓冲的前后缓冲交换方式，Discard为让系统自动决定，效率最高
	dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//与设备关联的窗口句柄，就是要绘制的窗口。
	dpp.hDeviceWindow = g_App->GetWnd();

	//窗口or全屏
	dpp.Windowed = true;

	//自动创建并维护深度缓存或模板缓存，就设true吧
	dpp.EnableAutoDepthStencil = true;

	//深度缓存或模板缓存的像素格式，D3DFMT_D24S8=用24位表示深度，8位保留供模板缓存使用
	dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	//附加特性，常用：D3DPRESENTFLAG_LOCKABLE_DEPTHBUFFER（可锁定后台缓存，会降低性能） D3DPRESENTFLAG_DISCARD_DEPTHBUFFER（下一个后台缓存提交时，那个深度或模板缓存将被丢弃）
	dpp.Flags = 0;

	//刷新频率
	dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	//显示时间间隔，默认为DEFAULT，由D3D来选择提交频率（一般为刷新频率）；IMMEDIATE为立即提交。
	dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;




	//创建设备
	//IDirect3DDevice9* p_device = 0;

	HRESULT hr = p_d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL/*HAL硬件，SW软件，REF引用（DEBUG软件，RELEASE硬件）*/, g_App->GetWnd(), vp/*vertex processing*/, &dpp, &m_pDevice);

	if (FAILED(hr)){
		::MessageBox(0, _T("#2 CreateDevice error"), 0, 0);
		return false;
	}

	//创建输入设备
	 

	//渲染模式、视角等的设置

	//g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);//渲染网格模式
	//g_Device->SetRenderState(D3DRS_LIGHTING, FALSE);//关闭光照
	/*
		D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMATRIX V;
		D3DXMatrixLookAtLH(&V, &position, &target, &up);//从position看向target的视角
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