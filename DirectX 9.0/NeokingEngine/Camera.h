#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Macro.h"

#define CAMERA Camera::GetInstance()

/**
 * @brief ī�޶� Ŭ����
 * @author Dayeol Hyeon
 */
class Camera
{
private:
	static Camera* instacne;

	D3DXVECTOR3		vEye;			/// ī�޶��� ���� ��ġ
	D3DXVECTOR3		vLookat;		/// ī�޶��� �ü� ��ġ
	D3DXVECTOR3		vUp;			/// ī�޶��� ��溤��

	D3DXVECTOR3		vView;			/// ī�޶� ���ϴ� �������⺤��
	D3DXVECTOR3		vCross;			/// ī������ ���麤�� cross( view, up )

	D3DXMATRIXA16	matView;		/// ī�޶� ���
	D3DXMATRIXA16	matBill;		/// ������ ���(ī�޶��� �����)

public:
	Camera();
	virtual ~Camera();

	void			Init();

	/**
	* @brief ī�޶� ����� ����.
	*/
	D3DXMATRIXA16*	GetViewMatrix() { return &matView; }

	/**
	* @brief ������ ����� ����.
	*/
	D3DXMATRIXA16*	GetBillMatrix() { return &matBill; }

	/**
	* @brief ī�޶� ����� �����ϱ����� �⺻ ���Ͱ����� �����Ѵ�.
	* @param D3DXVECTOR3* pvEye ī�޶��� ���� ��ġ
	* @param D3DXVECTOR3* pvLookat ī�޶��� �ü� ��ġ
	* @param D3DXVECTOR3* pvUp ī�޶��� ��溤��
	*/
	D3DXMATRIXA16*	SetView(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp);

	/**
	* @brief ī�޶��� ��ġ���� �����Ѵ�.
	* @param D3DXVECTOR3* pv ī�޶��� ���� ��ġ
	*/
	void			SetEye(D3DXVECTOR3* pv) { vEye = *pv; }

	/**
	* @brief ī�޶��� ��ġ���� ����.
	*/
	D3DXVECTOR3*	GetEye() { return &vEye; }

	/**
	* @brief ī�޶��� �ü����� �����Ѵ�.
	* @param D3DXVECTOR3* pv ī�޶��� �ü� ��ġ
	*/
	void			SetLookat(D3DXVECTOR3* pv) { vLookat = *pv; }

	/**
	* @brief ī�޶��� �ü����� ����.
	*/
	D3DXVECTOR3*	GetLookat() { return &vLookat; }

	/**
	* @brief ī�޶��� ��溤�Ͱ��� �����Ѵ�.
	* @param D3DXVECTOR3* pv ī�޶��� ��溤��
	*/
	void			SetUp(D3DXVECTOR3* pv) { vUp = *pv; }

	/**
	* @brief ī�޶��� ��溤�Ͱ��� ����.
	*/
	D3DXVECTOR3*	GetUp() { return &vUp; }

	/**
	* @brief ���� �����Ѵ�.
	*/
	void			Flush() { SetView(&vEye, &vLookat, &vUp); }

	/**
	* @brief  ī�޶� ��ǥ���� X������ angle��ŭ ȸ���Ѵ�.
	* @param float angle ����
	*/
	D3DXMATRIXA16*	RotateLocalX(float angle);

	/**
	* @brief  ī�޶� ��ǥ���� Y������ angle��ŭ ȸ���Ѵ�.
	* @param float angle ����
	*/
	D3DXMATRIXA16*	RotateLocalY(float angle);

	//	D3DXMATRIXA16*	RotateLocalZ( float angle );

	/**
	* @brief  ������ǥ���� *pv���� ��ġ�� �̵��Ѵ�.
	* @param D3DXVECTOR3* pv ��ġ ����
	*/
	D3DXMATRIXA16*	MoveTo(D3DXVECTOR3* pv);

	/**
	* @brief  ī�޶� ��ǥ���� X��������� dist��ŭ �����Ѵ�.(������ -dist�� ������ �ȴ�.)
	* @param float dist �̵���
	*/
	D3DXMATRIXA16*	MoveLocalX(float dist);

	/**
	* @brief  ī�޶� ��ǥ���� Y��������� dist��ŭ �����Ѵ�.(������ -dist�� ������ �ȴ�.)
	* @param float dist �̵���
	*/
	D3DXMATRIXA16*	MoveLocalY(float dist);

	/**
	* @brief  ī�޶� ��ǥ���� Z��������� dist��ŭ �����Ѵ�.(������ -dist�� ������ �ȴ�.)
	* @param float dist �̵���
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

