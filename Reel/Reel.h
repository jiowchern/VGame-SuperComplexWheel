// �U�C ifdef �϶��O�إߥ����H��U�q DLL �ץX���зǤ覡�C
// �o�� DLL �����Ҧ��ɮ׳��O�ϥΩR�O�C���ҩw�q REEL_EXPORTS �Ÿ��sĶ���C
// �b�R�O�C�w�q���Ÿ��C����M�׳������w�q�o�ӲŸ�
// �o�ˤ@�ӡA��l�{���ɤ��]�t�o�ɮת������L�M��
// �|�N REEL_API �禡�����q DLL �פJ���A�ӳo�� DLL �h�|�N�o�ǲŸ�����
// �ץX���C
#ifdef REEL_EXPORTS
#define REEL_API __declspec(dllexport)
#else
#define REEL_API __declspec(dllimport)
#endif


namespace TESTENTEND
{
	class REEL_API Test
	{
		void Func();
	};
}
// �o�����O�O�q Reel.dll �ץX��
class REEL_API CReel {
public:
	CReel(void);
	// TODO:  �b���[�J�z����k�C
};

extern REEL_API int nReel;

REEL_API int fnReel(void);
