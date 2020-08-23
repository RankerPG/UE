# RPG 프로젝트

- 기본 전투
- PVP or 배틀로얄 모드 개발
~ 20.10.31까지 완료 목표
- 1차 목표는 20.09.15

<hr/>

### 9주차 20.08.17 ~ 20.08.23

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
