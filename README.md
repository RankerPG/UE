# RPG 프로젝트

- 기본 전투
~ 20.10.31까지 완료 목표

<hr/>

### 8주차 20.10.26 ~ 20.11.01

#### 추가사항

#### 수정사항
- IceSpike 1개가 삭제 되지 않던 현상 수정 ( 타이머의 시간이 0이면 타이머가 만들어지지 않아 Destroy가 호출되지 않던 버그 )

#### 버그
- 몬스터나 플레이어가 서로 충돌시 날아가는 현상 ( 사라진 듯 하면서도 더 지켜봐야 함 )
- 스킬중 점프 막기 필요
- CharacterHUD에서 SetPercent 도중 터지는 현상

### 7주차 20.10.12 ~ 20.10.18

#### 추가사항
- 데미지 폰트 추가
- 몬스터 정보 HUD 추가
- 몬스터 총알 데미지 적용
- 스킬 사운드 추가 ( 좀 더 추가해야 됨 )
- 재질별 발자국 사운드 추가
- 랜드스케이프에 레이어와 폴리지 추가

#### 수정사항
- E 스킬이 얼음 덫을 원형으로 설치하는 스킬로 변경됨 ( 몬스터와 충돌하면 몬스터는 데미지를 입고 프로즌 상태가 된다. )
- E 스킬이 랜드스케이프 위에 생성되도록 변경

#### 버그
- 몬스터나 플레이어가 서로 충돌시 날아가는 현상 ( 사라진 듯 하면서도 더 지켜봐야 함 )
- 스킬중 점프 막기 필요
- IceSpike 1개가 삭제 안되는 현상

#### 비고
- 액터에 넣은 유저 위젯이 SetWidgetClass해도 바로 NativeConstruct를 호출하는 게 아니라서 이 부분에서 버그가 많이 발생한다.

<hr/>

### 6주차 20.08.24 ~ 20.08.30

#### 추가사항
< 캐릭터 > 
- 애니메이션 상태와 분리하여 캐릭터 상태 자체를 가지는 enum 값 추가 ( Running, Frozen, Stun, Knockback )
- 애니메이션 재생속도를 조절할 수 있도록 하는 애님 노티파이 추가 ( 딜레이에 대해 조절 가능 )
- 플레이어와 몬스터 애님인스턴스가 상속받는 슈퍼애님인스턴스 추가 ( 서로 공유하는 함수가 많았고 같은 기능이지만 함수 이름이나 매개변수가 다르던 점을
통일화)
- 플레이어 & 몬스터 스턴, 넉백 상태 추가
- CC에 걸릴 때의 우선순위는 최근에 걸린 CC를 우선시한다.

< 플레이어 >
- 피격 애니메이션 삭제 & 스턴 애니메이션 추가 ( 모든 공격에 피격 판정하면 플레이가 끊기는 느낌이 강해서 스턴과 같은 CC만 처리하도록 변경 )
- 기본 공격, 회피에 트레일과 이펙트 추가
- 오로라 E 스킬 : 하단 베기 - 적을 프로즌 상태로 만든다. ( 슬로우로 바꿀지 고민 )
- 오로라 Q 스킬 : 돌진 - 적을 넉백 시키며 끌고가서 스턴 상태로 만든다. ( 스턴 파티클이 있지만 좀 더 가시성 있는 것으로 변경 필요 )
- 오로라 R 스킬 : 프로즌 월드 - 캐릭터 포워드 벡터를 기준으로 45도 각도에 있는 거리 2000까지의 몬스터를 프로즌 상태로 만든다. ( 스킬 범위 가시성 필요 )

< 몬스터 >
- 몬스터의 프로즌 상태 추가 ( 애니메이션이 멈추고 지정한 시간 후에 다시 애니메이션이 재생된다 )
- 프로즌 상태일 때 얼음 파티클 생성

< UI >
- 플레이어 HP, MP에 대한 HUD 위젯 추가
- 플레이어 상태 정보 위젯 추가
- 마우스 커서 On/Off 키 추가 ( Ctrl )
- 플레이어 상태 위젯 On/Off 할 수 있는 버튼 추가

#### 수정사항
- 회피시 블렌딩 포즈가 아니라 따로 스테이트를 둠으로써 회피 애니메이션 버그 수정
- 공격 중 회피 사용이 가능하도록 수정
- 전체적인 소스코드 점검
- 정찰 애니메이션 중에 멈추던 버그 수정 ( 스폰 포인트가 공중에 떠있어서 생기던 현상 )
- 상태 값을 무조건 정상으로 바꿔서 생기던 버그 수정
- CC 상태일 때도 애니메이션은 바뀌지만 이동하던 버그 수정

#### 버그
- 몬스터나 플레이어가 서로 충돌시 날아가는 현상 ( 사라진 듯 하면서도 더 지켜봐야 함 )

<hr/>

### 5주차 20.08.17 ~ 20.08.23

#### 추가사항
< 플레이어 >
- 플레이어 이동에 대한 8방향 애니메이션 추가
- 4방향 대시 스킬 추가
- 피격 모션 추가
- 점프 공격 충돌 체크 추가

< 애니메이션 >
- 애니메이션 블루프린트와 몽타주, 플레이어캐릭터 블루프린트를 활용해서 상하체 분리하여 기본 공격 중 이동 기능 구현
- 달리기 디테일 추가 ( 달리기 시작, 멈춤을 추가하고 블렌딩을 이용해서 구현했는데 블렌딩에 대해서 더 알아봐야 할 거 같음 )
- 애디티브 애니메이션을 통한 착지 후 블렌딩 개선
- 점프 공격 블루프린트로 구현

< 몬스터 >
- 원거리 몬스터 공격 추가 ( 디스트럭터블 메쉬 )
- 순찰 애니메이션 변경 및 이동 속도 조절

< UI >
- 시작레벨 생성 후 위젯의 버튼을 통해 메인 레벨로 이동과 게임 종료 기능 추가

#### 수정사항
- 착지 애니메이션이 계속 실행되던 버그 수정
- 공격 도중 대시를 사용하면 대기 or 달리기 애니메이션으로 바로 옮겨지는 버그 수정 ( 공격 애니메이션의 나가는 스테이트 이벤트에서 대기로 변경해서 생긴 버그 )
- 플레이어 기본 공격 충돌체를 캡슐에서 박스로 변경 ( 캡슐보다 더 판정이 좋게 느껴져서 바꿈 )
- 플레이어 캐릭터 신비 -> 오로라로 변경 ( 애니메이션이 더 다양해서 변경 )

#### 버그
- 간헐적으로 몬스터 애니메이션이 멈추는 현상
- 몬스터나 플레이어가 서로 충돌시 날아가는 현상
- 이베이드 끝나고 대기로 돌아갈 때 RunNone 애니메이션이 실행되는 현상
- 시간이 긴 애니메이션이 진행될 때 이미 애니메이션 상태 값은 변경되었지만 계속 진행중인 현상

<hr/>

### 4주차 20.07.13 ~ 20.07.19

#### 추가사항
< 몬스터 기본 AI 제작 >

- 플레이어 와의 거리에 따라 공격, 추적, 순찰의 행동을 하는 몬스터 행동 트리 구현
- 행동 트리와 블랙 보드 생성 후 MonsterAIController와 연결
- MonsterAIController에서 블랙보드 값에 접근할 수 있는 get/set 함수 추가

< Service >
- Detect : 탐지 범위 안에 플레이어가 있는지 체크하고 있을 경우 Target에 플레이어를 넣어줌

< decorator >
- InAttackRange : 공격 범위 안에 플레이어가 있는지 여부 판단

< Task >
- attack : 공격 범위 안에 플레이어가 있으면 공격
- MoveToTarget : 공격 범위 안에 플레이어가 없으면 추적
- Patrol : 탐지할 수 있는 범위 안에 플레이어가 없으면 PatrolPoint 배열 값을 참조하여 순찰


#### 버그
- 플레이어 점프 후 착지시 이동하는 과정에서 계속 착지를 시도하는 애니메이션 발생

<hr/>

### ~3주차 20.06.28 ~ 20.07.12

#### 추가사항 ( 지난 내용이라 간략화 )
< 캐릭터 객체 생성 ( PlayerCharacter, PlayerAnimInstance ) 및 애니메이션 생성 >
- 대기, 공격, 점프, 점프 공격, 스폰, 달리기, 스킬(파이어 볼) 애니메이션 생성
- 몬스터 객체 생성
- 몬스터 스폰 포인트 생성
- 파티클 시스템, 이펙트 객체 생성
- 이펙트 사운드 객체 생성
- 플레이어 공격시 충돌판정과 이펙트 생성
- 데이터테이블을 활용한 몬스터 정보 불러오기

#### 버그
- 플레이어 점프 후 착지시 이동하는 과정에서 계속 착지를 시도하는 애니메이션 발생
