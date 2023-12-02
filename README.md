# MyUnrealProject
2023-11-30
중간부터 언리얼과 깃허브를 연동하게 되어 지금부터 작성합니다.
이전까지는 캐릭터 움직임과 공격 애니메이션을 구현하였습니다.

공격에 대한 타격 판정을 만들었습니다.
우선 적 인스턴스에 대해 physics body를 만들어서 overlap event를 발생할 수 있게 합니다.
무기에는 타격 부분에 hit capsule을 만들어서 overlap event를 발생할 수 있게 합니다.
타격 판정 시점을 정확하게 판단하기 위해 anim notify를 사용합니다.
타격판정 시작부분과 끝부분에 각각 anim notify를 만들고 시작부분을 지나면 IsAttackPossible변수를 true로, 끝 부분을 지나면 IsAttackPossible을 false로 설정합니다.
이것 만으로는 판단할 수 없기에 무기의 hit capsule에 OnComponentBeginOverlap을 사용합니다. 
IsAttackPossible이 true인 상태로 겹침 이벤트가 발생했다면 타격 판정을 실행합니다. 
이미 겹쳐 있는 상태에서 공격을 할 수도 있기 때문에 공격이 아닌 상태에서 겹침이 발생한다면 IsAttackPossible을 true로 설정하고 타격 판정 시작 ainm notify를 true인 채로 지나면 타격 판정이 일어나도록 합니다.
IsAttackPossible이 계속 true가 되면 안되므로 OnComponentEndOverlap을 통해 겹침이 끝나면 IsAttackPossible을 false로 설정합니다.
다음엔 판정 후 무엇을 할 것인지 만들겠습니다.
