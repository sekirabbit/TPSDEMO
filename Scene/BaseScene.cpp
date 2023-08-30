#include "Headers.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
Math::Vector3 GetDot(const Math::Vector3& _rayVec, const Math::Vector3& _normal)
{
	//進入角度を算出
	Math::Vector3 dot;
	Math::Vector3 toVec;
	toVec = _rayVec;
	//壁の法線と移動方向の逆向きベクトルで内積を求める
	dot = DirectX::XMVector3Dot(_normal, -toVec);

	return dot;
}



//モデルのあたり判定関数
bool ModelIntersects(const KdModel& _model, const Math::Matrix& _mat, const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec)
{
	float nearestDist = FLT_MAX;	//FLT_MAX==float型の最大値

	Math::Vector3 hitVPos[3];		//レイが当たったポリゴンの３頂点座標
	Math::Matrix hitMat;			//レイが当たったポリゴンの行列

	for (auto&& node : _model.GetAllNodes())
	{
		//メッシュが含まれていないノードなら飛ばす
		if (node.Mesh == nullptr)continue;

		//そのノードのワールド行列を取得
		Math::Matrix worldMat = node.LocalTransform * _mat;

		//逆行列化
		Math::Matrix inv = worldMat.Invert();

		//逆行列を使ってローカル座標に変換
		Math::Vector3 localPos = DirectX::XMVector3Transform(_rayPos, inv);
		Math::Vector3 localDir = DirectX::XMVector3TransformNormal(_rayVec, inv);

		//拡大行列を使っているメッシュ用にレイの長さを計っておく
		float rayLen = localDir.Length();

		//方向は必ず長さ１にする
		localDir.Normalize();

		//メッシュ内の全ポリゴンを回す
		for (auto&& face : node.Mesh->GetFaces())
		{
			float dist;

			Math::Vector3 vPos[3];//今回レイ判定するポリゴンの３頂点座標
			vPos[0] = node.Mesh->GetVertexPositions()[face.Idx[0]];
			vPos[1] = node.Mesh->GetVertexPositions()[face.Idx[1]];
			vPos[2] = node.Mesh->GetVertexPositions()[face.Idx[2]];

			bool hit = DirectX::TriangleTests::Intersects(
				localPos,
				localDir,
				vPos[0],//１頂点目の座標
				vPos[1],//２頂点目の座標
				vPos[2],//３頂点目の座標
				dist	//レイが当たったところまでの距離(参照型)
			);

			if (hit == false)continue;

			//拡大分を反映
			dist /= rayLen;

			//もっとも近い距離を残す
			if (dist < nearestDist)
			{
				nearestDist = dist;

				//レイが当たったポリゴンの頂点座標を保存
				hitVPos[0] = vPos[0];
				hitVPos[1] = vPos[1];
				hitVPos[2] = vPos[2];

				//レイが当たったポリゴンの行列を保存
				hitMat = worldMat;
			}
		}
	}
	if (nearestDist == FLT_MAX)
	{
		return false;
	}
	else {
		_dis = nearestDist;

		//ポリゴンの辺を表すベクトルを求める
		Math::Vector3 vec1, vec2;
		vec1 = hitVPos[1] - hitVPos[0];
		vec2 = hitVPos[2] - hitVPos[0];

		//ポリゴン二辺に対する外積（=そのポリゴンの法線）
		Math::Vector3 Cross;
		Cross = DirectX::XMVector3Cross(vec1, vec2);

		//法線を現在のモデルの向きに合わせて回転
		_normalVec = DirectX::XMVector3TransformNormal(Cross, hitMat);

		//法線の正規化
		_normalVec.Normalize();

		return true;
	}
}



//引数で受け取ったベクトルの
//▲(0,0,1)に対しての左右角度を戻り値で返す
float GetVecAngY(const Math::Vector3& _vec)
{
	Math::Vector3 vec = _vec;
	vec.y = 0;
	vec.Normalize();
	Math::Vector3 dot;
	dot = DirectX::XMVector3Dot(Math::Vector3(0, 0, 1), vec);

	if (dot.x > 1)
	{
		dot.x = 1;
	}
	if (dot.x < -1)
	{
		dot.x = -1;
	}
	float angY;
	angY = DirectX::XMConvertToDegrees(acos(dot.x));
	if (vec.x < 0)
	{
		angY *= -1;
	}




	return angY;
}



//mat行列で管理されたキャラクターを
//_targetAng度方向に_plusAng度回転させ、
//_targetAng度までの残り角度を戻り値で返す
float TurnToAng(Math::Matrix& _mat, const float _targetAng, const float _plusAng)
{
	float currentAng;
	currentAng = GetVecAngY(_mat.Backward());
	//_mat.BackWard() => 行列の前方ベクトル
	//右手座標と左手座標の違いからBackwardが前方を表す
	float lastAng;
	lastAng = _targetAng - currentAng;
	//+180 ～ -180の範囲にする
	while (lastAng > 180)
	{
		lastAng -= 360;
	}
	while (lastAng < -180)
	{
		lastAng += 360;
	}
	Math::Matrix tmpMat;
	if (lastAng > _plusAng)//目標角度は右方向
	{
		tmpMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_plusAng));
		lastAng -= _plusAng;
	}
	else
	{
		if (lastAng < -_plusAng)//目標角度は左方向
		{
			tmpMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(-_plusAng));
			lastAng += _plusAng;
		}
		else//目標角度まで_plusAng度以下である
		{
			tmpMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(lastAng));
			lastAng = 0;
		}
	}
	_mat = tmpMat * _mat;
	return lastAng;
}



//移動関連関数
Math::Vector3 MoveVec(const float& _ang, const Math::Vector3& _vec)
{
	Math::Vector3 moveVec = {};
	Math::Matrix rotMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_ang));
	moveVec += DirectX::XMVector3TransformNormal(_vec, rotMat);
	return moveVec;
}



//レイ判定関連関数
Math::Vector3 GetLookVec(const float& _angX, const float& _angY)
{
	//ー－－－－－－－－－－－－－－－－－
	Math::Vector3 LookVec;//見てる方向
	Math::Matrix mat;//合成した向き方向
	Math::Matrix rotXMat;//X軸で回転するの角度
	Math::Matrix rotYMat;//Y軸で回転するの角度

	rotXMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(_angX));
	rotYMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(_angY));
	mat = rotXMat * rotYMat;
	//ー－－－－－－－－－－－－－－－－－－－－－－

	LookVec = XMVector3TransformNormal(Math::Vector3(0, 0, 1), mat);

	return LookVec;
}



//法線取得
Math::Vector3 GetNormal(const Math::Matrix& _mat)
{
	Math::Vector3 normalVec;
	//															向きは真逆方向
	normalVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, -1), _mat);

	return normalVec;
}


//キーフレームアニメーション
void AnimeProc(Math::Matrix& _startMat, Math::Matrix& _endMat, const float _animeFrame, Math::Matrix& _mat)
{
	Math::Quaternion startQua;
	Math::Quaternion endQua;
	Math::Quaternion nowQua;

	//最初と最後の行列からクォータニオンを作成
	startQua = DirectX::XMQuaternionRotationMatrix(_startMat);
	endQua = DirectX::XMQuaternionRotationMatrix(_endMat);

	//中間行列を求める(Slerp:スライド　| エス　ラープ)
	nowQua = DirectX::XMQuaternionSlerp(startQua, endQua, _animeFrame);;
	_mat = DirectX::XMMatrixRotationQuaternion(nowQua);

	//中間座標を求める
	Math::Vector3 startPos;
	Math::Vector3 endPos;
	Math::Vector3 nowPos;

	//最初と最後の位置を求める(Get translation)
	startPos = _startMat.Translation();
	endPos = _endMat.Translation();

	//中間座標を求める(Lerpラープ)
	nowPos = DirectX::XMVectorLerp(startPos, endPos, _animeFrame);

	//中間座標を行列にセット(Set translation)
	_mat.Translation(nowPos);
}


//当たり判定（円判定）
bool AttackCheck(Math::Vector3 _attackVec, Math::Vector3 _damageVec, float _hitDis)
{
	//攻撃側と被ダメージ側の距離
	Math::Vector3 attackDis;
	attackDis = _damageVec - _attackVec;

	if (attackDis.Length() <= _hitDis)
	{
		return true;

	}
	return false;
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------


BaseScene::BaseScene()
{
	m_sound = new Sound();
	m_changeSceneWaitTime = ChangeSceneWaitTime;
}

BaseScene::~BaseScene()
{
	delete m_sound;
}

void BaseScene::Frame()
{
	APP.m_console.ClearLog();
	// ゲーム更新処理
	Update();
	// ライトのデータを書き込む
	SHADER.m_cb8_Light.Write();
	//画面をクリア
	// バックバッファクリア
	D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer()->GetRTView(), Math::Color(0.0f, 0.0f, 0.0f, 1.0f));//RGBAを0-1の範囲で
	// Zバッファクリア
	D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer()->GetDSView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	
	SetCamera();
	//テクスチャに描画
	DynamicDraw();
	// ゲーム描画処理
	Draw();
}

void BaseScene::SetCamera()
{
}

void BaseScene::Update()
{
}

void BaseScene::ImGuiUpdate()
{
}

void BaseScene::Draw()
{
}

void BaseScene::DynamicDraw()
{
}

