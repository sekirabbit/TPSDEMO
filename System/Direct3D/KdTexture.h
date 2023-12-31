#pragma once

//====================================================
//
// テクスチャクラス
//
//====================================================
class KdTexture
{
public:

	//====================================================
	//
	// 取得
	//
	//====================================================

	// 画像のアスペクト比取得
	float								GetAspectRatio() const { return (float)m_desc.Width / m_desc.Height; }
	// 画像の幅を取得
	UINT								GetWidth() const { return m_desc.Width; }
	// 画像の高さを取得
	UINT								GetHeight() const { return m_desc.Height; }
	// 画像の全情報を取得
	const D3D11_TEXTURE2D_DESC&			GetInfo() const { return m_desc; }
	// ファイルパス取得(Load時のみ)
	const std::string&					GetFilepath() const { return m_filepath; }


	// 画像リソースを取得
	ID3D11Texture2D*					GetResource() const;

	// シェーダリソースビュー取得
	ID3D11ShaderResourceView*			GetSRView() const { return m_srv; }
	// シェーダリソースビューのアドレス取得
	ID3D11ShaderResourceView* const*	GetSRViewAddress() const { return &m_srv; }

	// レンダーターゲットビュー取得
	ID3D11RenderTargetView*				GetRTView() const { return m_rtv; }
	// レンダーターゲットビューのアドレス取得
	ID3D11RenderTargetView* const*		GetRTViewAddress() const { return &m_rtv; }

	// 深度ステンシルビュー取得
	ID3D11DepthStencilView*				GetDSView() const { return m_dsv; }

	//====================================================
	//
	// 画像ファイルからテクスチャ作成
	//
	//====================================================

	// 画像ファイルを読み込む
	// ・filename		… 画像ファイル名
	// ・renderTarget	… レンダーターゲットビューを生成する(レンダーターゲットにする)
	// ・depthStencil	… 深度ステンシルビューを生成する(Zバッファにする)
	// ・generateMipmap	… ミップマップ生成する？
	bool Load(const std::string& filename, bool renderTarget = false, bool depthStencil = false, bool generateMipmap = false);

	//====================================================
	//
	// テクスチャ作成
	//
	//====================================================

	// リソースから作成
	// ・pTexture2D	… 画像リソース
	// 戻り値：true … 成功
	bool Create(ID3D11Texture2D* pTexture2D);

	// desc情報からテクスチャリソースを作成する
	// ・desc		… 作成するテクスチャリソースの情報
	// ・fillData	… バッファに書き込むデータ　nullptrだと書き込みなし
	// 戻り値：true … 成功
	bool Create(const D3D11_TEXTURE2D_DESC& desc, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);

	// 通常テクスチャとして作成
	// ※テクスチャリソースを作成し、ShaderResourceViewのみを作成します
	// ・w			… 画像の幅(ピクセル)
	// ・h			… 画像の高さ(ピクセル)
	// ・format		… 画像の形式　DXGI_FORMATを使用
	// ・arrayCnt	… 「テクスチャ配列」を使用する場合、その数。1で通常の1枚テクスチャ
	// ・fillData	… バッファに書き込むデータ　nullptrだと書き込みなし
	// 戻り値：true … 成功
	bool Create(int w, int h, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, UINT arrayCnt = 1, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);

	// レンダーターゲットテクスチャとして作成
	// ※テクスチャリソースを作成し、RenderTargetViewとShaderResourceViewの2種類を作成します
	// ・w			… 画像の幅(ピクセル)
	// ・h			… 画像の高さ(ピクセル)
	// ・format		… 画像の形式　DXGI_FORMATを使用
	// ・arrayCnt	… 「テクスチャ配列」を使用する場合、その数。1で通常の1枚テクスチャ
	// ・fillData	… バッファに書き込むデータ　nullptrだと書き込みなし
	// 戻り値：true … 成功
	bool CreateRenderTarget(int w, int h, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, UINT arrayCnt = 1, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);

	// Zバッファテクスチャとして作成
	// ※テクスチャリソースを作成し、DepthStencilViewとShaderResourceViewの2種類を作成します
	// ・w			… 画像の幅(ピクセル)
	// ・h			… 画像の高さ(ピクセル)
	// ・format		… 画像の形式　DXGI_FORMATを使用　32bit：DXGI_FORMAT_R32_TYPELESS  ステンシル付き：DXGI_FORMAT_R24G8_TYPELESS
	// ・arrayCnt	… 「テクスチャ配列」を使用する場合、その数。1で通常の1枚テクスチャ
	// ・fillData	… バッファに書き込むデータ　nullptrだと書き込みなし
	// 戻り値：true … 成功
	bool CreateDepth(int w, int h, DXGI_FORMAT format = DXGI_FORMAT_R32_TYPELESS, UINT arrayCnt = 1, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);


	//====================================================
	//
	// ビューから作成
	//
	//====================================================
	// ShaderResourceViewをセットする
	void SetSRView(ID3D11ShaderResourceView* srv);

	//描画先をテクスチャへ切り替える
	//CreateRenderTargetにて幅と高さがバックバッファと同じ時のみ有効
	//※違う場合はZバッファ設定、ビューポートの設定が必須
	/*void SetRenderTarget()
	{
		D3D.GetDevContext()->OMSetRenderTargets(1, &m_rtv, D3D.GetZBuffer()->GetDSView());
	}*/
	void SetRenderTarget(ID3D11RenderTargetView* _rtv = nullptr)
	{
		ID3D11RenderTargetView* rtv[2] = { m_rtv ,_rtv };
		D3D.GetDevContext()->OMSetRenderTargets(
			2,
			rtv,
			D3D.GetZBuffer()->GetDSView());
	}


	// 
	KdTexture() {}

	//====================================================
	// 解放
	//====================================================
	void Release();

	// 
	~KdTexture()
	{
		Release();
	}

private:

	// シェーダリソースビュー(読み取り用)
	ID3D11ShaderResourceView*	m_srv = nullptr;
	// レンダーターゲットビュー(書き込み用)
	ID3D11RenderTargetView*		m_rtv = nullptr;
	// 深度ステンシルビュー(Zバッファ用)
	ID3D11DepthStencilView*		m_dsv = nullptr;

	// 画像情報
	D3D11_TEXTURE2D_DESC		m_desc = {};

	// 画像ファイル名(Load時専用)
	std::string					m_filepath;

private:
	// コピー禁止用
	KdTexture(const KdTexture& src) = delete;
	void operator=(const KdTexture& src) = delete;
};
