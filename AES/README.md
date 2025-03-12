이 코드는 AES 알고리즘의 핵심적인 기능을 C코드로 구현한 것입니다.

-SBox 및 SBoxInvert-
![image](https://github.com/user-attachments/assets/d3c20ab5-ddf5-4e19-b4e0-eef6e60b7652)
이 테이블은 AES에서 사용하는 바이트 치환 테이블입니다.
SBox는 바이트를 변환하는 데 사용되며, SBoxInvrt는 복호화 시 원래 값으로 복원할 때 사용됩니다.

-Key Expansion-
![image](https://github.com/user-attachments/assets/69ab79b5-380e-4bb2-9bc0-7ffafd5644ca)
키 확장 연산입니다.
AES는 입력 키(128비트)를 확장하여 10개의 라운드 키를 생성해야 합니다.
KeyExpansion 함수는 원래 키(Key)를 ExpKey에 확장하여 저장합니다.
Rcon 배열은 키 확장에서 사용되는 일정한 값(라운드 상수)입니다.

-라운드 연산-
![image](https://github.com/user-attachments/assets/bd50faf4-9684-41a8-b20d-e003e9ee1cba)
AddRoundKey: 현재 상태에 라운드 키를 XOR 연산으로 추가합니다.
SubBytes: SBox를 이용하여 바이트 치환을 수행합니다.
ShiftRows: AES의 행 이동 연산을 수행합니다.
MixColumns: AES의 열 혼합 연산을 수행합니다.
InvSubBytes(), InvShiftRows(), InvMixColumns(): 복호화 과정에서 사용하는 연산들입니다.

-실행 결과-
![image](https://github.com/user-attachments/assets/62004fba-e5a2-41f0-859e-d4592b9255e5)
