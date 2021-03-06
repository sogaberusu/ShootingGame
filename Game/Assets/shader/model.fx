/*!
 * @brief	モデルシェーダー。
 */
 

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);
/*!
 *@brief	空用のピクセルシェーダー。
 */
TextureCube<float4> skyCubeMap : register(t2);		//スカイキューブマップ。
Texture2D<float4> g_shadowMap : register(t3);		//シャドウマップ。
/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//todo ライトビュー行列を追加。
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	int isShadowReciever;	//シャドウレシーバーフラグ。
};

static const int NUM_DIRECTION_LIG = 4;

////ディレクションライト。
//struct SDirectionLight {
//	float3 direction;
//	float4 color;
//};
////ライト用の定数バッファ
// cbuffer LightCb : register(b1) {
//	 SDirectionLight	directionLight;		//ディレクションライト。
//	 float3				eyePos;				//カメラの視点。
//	 float				specPow;			//スペキュラライトの絞り。
// };

/// <summary>
/// ライト用の定数バッファ。
/// </summary>
cbuffer LightCb : register(b1) {
	float3 dligDirection[NUM_DIRECTION_LIG];
	float4 dligColor[NUM_DIRECTION_LIG];
};
 
/// シャドウマップ用の定数バッファ。
 cbuffer ShadowMapCb : register(b1) {
	 float4x4 lightViewProjMatrix;	//ライトビュープロジェクション行列。
 }
/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//ワールド座標
	float4 posInLVP		: TEXCOORD2;	//ライトビュープロジェクション空間での座標。
};
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//座標。
};
/// シャドウマップ用のピクセルシェーダへの入力構造体。
struct PSInputSkin_ShadowMap {
	float4 Position : SV_POSITION;	//座標。
	float3 Normal   : NORMAL;		//法線。
	float2 TexCoord	: TEXCOORD0;	//UV座標。
	float3 Tangent	: TANGENT;		//接ベクトル。
	uint4  Indices  : BLENDINDICES0;//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
	float4 Weights  : BLENDWEIGHT0;	//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
	float3 worldPos	: TEXCOORD1;	//ワールド座標
	float4 posInLVP	: TEXCOORD2;	//ライトビュープロジェクション空間での座標。
};
/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}


/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	//PSInput psInput = (PSInput)0;
	////ローカル座標系からワールド座標系に変換する。
	//float4 pos = mul(mWorld, In.Position);
	////鏡面反射の計算のために、ワールド座標をピクセルシェーダーに渡す。
	//psInput.worldPos = pos;

	//pos = mul(mView, pos);
	//pos = mul(mProj, pos);
	//psInput.Position = pos;

	//if (isShadowReciever == 1) {
	//	//続いて、ライトビュープロジェクション空間に変換。
	//	psInput.posInLVP = mul(mLightView, pos);
	//	psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	//}


	////UV座標はそのままピクセルシェーダーに渡す。
	//psInput.TexCoord = In.TexCoord;
	////法線はそのままピクセルシェーダーに渡す。
	//psInput.Normal = normalize(mul(mWorld, In.Normal));
	//psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	//return psInput;


	PSInput psInput = (PSInput)0;
	//ローカル座標系からワールド座標系に変換する。
	float4 worldPos = mul(mWorld, In.Position);
	//ワールド座標系からカメラ座標系に変換する。
	psInput.Position = mul(mView, worldPos);
	//カメラ座標系からスクリーン座標系に変換する。
	psInput.Position = mul(mProj, psInput.Position);

	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	//UV座標はそのままピクセルシェーダーに渡す。
	psInput.TexCoord = In.TexCoord;
	//法線はそのままピクセルシェーダーに渡す。
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	

	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
	}
	psInput.worldPos = pos;
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}

/*!
 *@brief	空用のシェーダー。
 */
float4 PSMain_SkyCube(PSInput In) : SV_Target0
{
	float4 color = skyCubeMap.Sample(Sampler, In.Normal);
	return color;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	////albedoテクスチャからカラーをフェッチする。
	//float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	////ディレクションライトの拡散反射光を計算する。
	//float3 lig = max(0.0f, dot(In.Normal * -1.0f, directionLight.direction)) * directionLight.color.xyz;
	////ディレクションライトの鏡面反射光を計算する。
	//{
	//	//実習　鏡面反射を計算しなさい。
	//	//�@ ライトを当てる面から視点に伸びるベクトルtoEyeDirを求める。
	//	//	 視点の座標は定数バッファで渡されている。LightCbを参照するように。
	//	float3 toEyeDir = normalize(eyePos - In.worldPos);//In.worldPos - eyePos; 
	//	//toEyeDir = normalize(toEyeDir);
	//	//�A １で求めたtoEyeDirの反射ベクトルを求める。
	//	float3 reflectEyeDir = -toEyeDir + 2 * dot(In.Normal, toEyeDir) * In.Normal;
	//	//float3 R = reflect(toEyeDir, In.Normal);
	//	//�B ２で求めた反射ベクトルとディレクションライトの方向との内積を取って、スペキュラの強さを計算する。
	//	float t = max(0.0f, dot(-directionLight.direction, reflectEyeDir));
	//	//float spec = max(0.0f, dot(-R, directionLight.direction));

	//	//�C pow関数を使って、スペキュラを絞る。絞りの強さは定数バッファで渡されている。
	//	//	 LightCbを参照するように。
	//	float3 specLig = pow(t, specPow) * directionLight.color.xyz;
	//	//float3 specLig = pow(spec,specPow);
	//	//specLig *= directionLight.color.xyz;
	//	//�D スペキュラ反射が求まったら、ligに加算する。
	//	//鏡面反射を反射光に加算する。
	//	lig += specLig;
	//}
	//if (isShadowReciever == 1) {	//シャドウレシーバー。
	//	//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
	//	float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
	//	shadowMapUV *= float2(0.5f, -0.5f);
	//	shadowMapUV += 0.5f;
	//	//シャドウマップの範囲内かどうかを判定する。
	//	if (shadowMapUV.x < 1.0f
	//		&& shadowMapUV.x > 0.0f
	//		&& shadowMapUV.y < 1.0f
	//		&& shadowMapUV.y > 0.0f
	//		) {

	//		///LVP空間での深度値を計算。
	//		float zInLVP = In.posInLVP.z / In.posInLVP.w;
	//		//シャドウマップに書き込まれている深度値を取得。
	//		float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

	//		if (zInLVP > zInShadowMap + 0.01f) {
	//			//影が落ちているので、光を弱くする
	//			lig *= 0.5f;
	//		}
	//	}
	//}
	//float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	//finalColor.xyz = albedoColor.xyz *lig;
	//return finalColor;



	//albedoテクスチャからカラーをフェッチする。
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);

	float3 lig = 0.0f;
	//ディレクションライトの拡散反射光を計算する。

	for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
		lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) * dligColor[i];
	}

	if (isShadowReciever == 1) {	//シャドウレシーバー。
		//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//シャドウマップの範囲内かどうかを判定する。
		if (shadowMapUV.x < 1.0f
			&& shadowMapUV.x > 0.0f
			&& shadowMapUV.y < 1.0f
			&& shadowMapUV.y > 0.0f
		) {

			///LVP空間での深度値を計算。
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//シャドウマップに書き込まれている深度値を取得。
			float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

			if (zInLVP > zInShadowMap + /*0.01f*/0.0005f) {
				//影が落ちているので、光を弱くする
				lig *= 0.5f;
			}
		}
	}
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}
/// <summary>
/// シャドウマップ生成用の頂点シェーダー。
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
/// <summary>
/// シャドウマップ生成用の頂点シェーダー。
/// </summary>
PSInputSkin_ShadowMap VSMainSkin_ShadowMap(VSInputNmTxWeights In)
{
	PSInputSkin_ShadowMap psInput = (PSInputSkin_ShadowMap)0;
	/*float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;*/

	//PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;

	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//最後のボーンを計算する。
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
		pos = mul(skinning, In.Position);
	}
	psInput.worldPos = pos;
	psInput.Normal = normalize(mul(skinning, In.Normal));
	psInput.Tangent = normalize(mul(skinning, In.Tangent));

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	
	return psInput;
}
/// <summary>
/// ピクセルシェーダーのエントリ関数。
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}

//--------------------------------------------------------------------------------------
// シルエット描画用のピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}