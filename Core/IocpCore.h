#pragma once
class IocpEvent; // ���� ����

class IocpObject : std::enable_shared_from_this<IocpObject>
{
public:
	IocpObject() = default;
	virtual ~IocpObject() = default;
public:
	virtual HANDLE GetHandle() = 0;
	virtual void Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes) = 0;
};

/// 
/// @class IocpCore
/// Iocp ��ü�� �����ϰ� �̺�Ʈ�� ����ϴ� Ŭ�����̴�.
/// IocpObject�� ��ӹ޴� ��ü�� ����ϰ� ��� ������ ť�� �����Ѵ�. IOCompletion Queue���� ��ȯ�Ǵ� ��� 
/// TID�� Windows Release IOCP Thread Queue�� �̵��Ѵ�.
/// 
class IocpCore
{
public:
	IocpCore();
	~IocpCore();
public:
	HANDLE GetHandle() { return m_hIocp; }
	bool Dispatch();
	bool Register(std::shared_ptr<IocpObject> pIocpObject);

private:
	HANDLE m_hIocp;
};

