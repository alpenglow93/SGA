#include <iostream>
using namespace std;


//敗呪(function): 耕軒 坪球研 拙失背兜壱 亜閃陥 床澗 依
//鋼発葵 敗呪誤(古鯵痕呪)
//鋼発葵(汽戚斗莫)	敗呪誤(績税旋生稽 憎澗陥)

void Function1(void)
{
	cout << "敗呪 砺什闘 " << endl;
}
void Function2(int num)
{
	cout << "古鯵痕呪 砺什闘: " << num << endl;
}
int SumNumber(int num1, int num2)
{
	int result = num1 + num2;
	return result;
}
//call by value(葵拭 税廃 硲窒) -> 檎羨
void Sum(int result, int num1, int num2)
{
	result = num1 + num2;
	cout << "敗呪 鎧採 域至: " << result << endl;
}
//敗呪 穿号識情: 敗呪亜 糎仙廃陥澗 依聖 陳濃斗拭 耕軒 硝形爽壱, 敗呪 識情精 焼掘拭 背層陥
float Mul(float num1, float num2);
float Mul(float num1);
float Mul(int num1);
//int Mul(int num1);
//敗呪 神獄稽漁(OverLoading): 敗呪 戚硯戚 旭焼亀 古鯵痕呪人 軒渡葵税 託戚拭 魚虞 陥献 敗呪稽 昔縦馬澗 奄管. 馬走幻 敗呪税 汽戚斗莫戚 陥献依精 旋遂鞠走 省澗陥.
//敗呪税 戚硯戚 旭壱 敗呪 昔切葵戚 陥献 敗呪級聖 陥献 敗呪稽 昔縦馬澗 奄管 -> 檎羨

void main()
{
	//紫遂拝 坪球澗 巷繕闇 main 照拭辞 拙失
	for (int i = 0; i < 2; i++)
	{
		Function1();
	}
	Function2(200);
	int nNumber = 400;
	Function2(nNumber);
	int nNumber2 = SumNumber(100, 200);
	cout << nNumber2 << endl;
	int nResult = 0, nNum1 = 10, nNum2 = 20;
	Sum(nResult, nNum1, nNum2);
	cout << "敗呪 曽戟 板 域至葵: " << nResult << endl;
	
	float fNum = Mul(10.25f, 4.6f);
	float fNum2 = Mul(24.0f);
	cout << fNum << endl;
	//神嫌...亜 貝陥澗汽 訊 照 貝陥劃.. 弘経 域至精 照鞠澗汽.
	//焼巷動 神嫌亜 蟹澗 戚政澗 坪球澗 是拭辞採斗 石嬢蟹亜奄 凶庚拭 Mul 敗呪亜 赤澗走 乞牽奄 凶庚拭 拭君研 浬陥
	//zzせせせせせせ 獣郊 戚暗 c++戚虞 益訓亜
}
float Mul(float num1, float num2)
{
	return num1 * num2;
}
float Mul(float num1)	
{
	return num1 * 100;
}