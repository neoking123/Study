#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Macro.h"

#define CAMERA Camera::GetInstance()

/**
 * @brief 카메라 클래스
 * @author Dayeol Hyeon
 */
class Camera
{
private:
	static Camera* instacne;

	D3DXVECTOR3		vEye;			/// 카메라의 현재 위치
	D3DXVECTOR3		vLookat;		/// 카메라의 시선 위치
	D3DXVECTOR3		vUp;			/// 카메라의 상방벡터

	D3DXVECTOR3		vView;			/// 카메라가 향하는 단위방향벡터
	D3DXVECTOR3		vCross;			/// 카마레의 측면벡터 cross( view, up )

	D3DXMATRIXA16	matView;		/// 카메라 행렬
	D3DXMATRIXA16	matBill;		/// 빌보드 행렬(카메라의 역행렬)

public:
	Camera();
	virtual ~Camera();

	void			Init();

	/**
	* @brief 카메라 행렬을 얻어낸다.
	*/
	D3DXMATRIXA16*	GetViewMatrix() { return &matView; }

	/**
	* @brief 빌보드 행렬을 얻어낸다.
	*/
	D3DXMATRIXA16*	GetBillMatrix() { return &matBill; }

	/**
	* @brief 카메라 행렬을 생성하기위한 기본 벡터값들을 설정한다.
	* @param D3DXVECTOR3* pvEye 카메라의 현재 위치
	* @param D3DXVECTOR3* pvLookat 카메라의 시선 위치
	* @param D3DXVECTOR3* pvUp 카메라의 상방벡터
	*/
	D3DXMATRIXA16*	SetView(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp);

	/**
	* @brief 카메라의 위치값을 설정한다.
	* @param D3DXVECTOR3* pv 카메라의 현재 위치
	*/
	void			SetEye(D3DXVECTOR3* pv) { vEye = *pv; }

	/**
	* @brief 카메라의 위치값을 얻어낸다.
	*/
	D3DXVECTOR3*	GetEye() { return &vEye; }

	/**
	* @brief 카메라의 시선값을 설정한다.
	* @param D3DXVECTOR3* pv 카메라의 시선 위치
	*/
	void			SetLookat(D3DXVECTOR3* pv) { vLookat = *pv; }

	/**
	* @brief 카메라의 시선값을 얻어낸다.
	*/
	D3DXVECTOR3*	GetLookat() { return &vLookat; }

	/**
	* @brief 카메라의 상방벡터값을 설정한다.
	* @param D3DXVECTOR3* pv 카메라의 상방벡터
	*/
	void			SetUp(D3DXVECTOR3* pv) { vUp = *pv; }

	/**
	* @brief 카메라의 상방벡터값을 얻어낸다.
	*/
	D3DXVECTOR3*	GetUp() { return &vUp; }

	/**
	* @brief 값을 갱신한다.
	*/
	void			Flush() { SetView(&vEye, &vLookat, &vUp); }

	/**
	* @brief  카메라 좌표계의 X축으로 angle만큼 회전한다.
	* @param float angle 각도
	*/
	D3DXMATRIXA16*	RotateLocalX(float angle);

	/**
	* @brief  카메라 좌표계의 Y축으로 angle만큼 회전한다.
	* @param float angle 각도
	*/
	D3DXMATRIXA16*	RotateLocalY(float angle);

	//	D3DXMATRIXA16*	RotateLocalZ( float angle );

	/**
	* @brief  월드좌표계의 *pv값의 위치로 이동한다.
	* @param D3DXVECTOR3* pv 위치 벡터
	*/
	D3DXMATRIXA16*	MoveTo(D3DXVECTOR3* pv);

	/**
	* @brief  카메라 좌표계의 X축방향으로 dist만큼 전진한다.(후진은 -dist를 넣으면 된다.)
	* @param float dist 이동량
	*/
	D3DXMATRIXA16*	MoveLocalX(float dist);

	/**
	* @brief  카메라 좌표계의 Y축방향으로 dist만큼 전진한다.(후진은 -dist를 넣으면 된다.)
	* @param float dist 이동량
	*/
	D3DXMATRIXA16*	MoveLocalY(float dist);

	/**
	* @brief  카메라 좌표계의 Z축방향으로 dist만큼 전진한다.(후진은 -dist를 넣으면 된다.)
	* @param float dist 이동량
	*/
	D3DXMATRIXA16*	MoveLocalZ(float dist);

	static Camera* GetInstance()
	{
		if (instacne == nullptr)
		{
			instacne = new Camera();
		}
		return instacne;
	}

	static void FreeInstance()
	{
		if (instacne != nullptr)
		{
			SAFE_DELETE(instacne);
		}
	}
};

