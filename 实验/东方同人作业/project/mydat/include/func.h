extern void boss_shot_bulletH000();
extern void boss_shot_bulletH001();
extern void boss_shot_bulletH002();
extern void boss_shot_bulletH003();
extern void boss_shot_bulletH004();
extern void boss_shot_bulletH005();
extern void boss_shot_bulletH006();
extern void boss_shot_bulletH007();
extern void boss_shot_bulletH008();
extern void boss_shot_bulletH009();
extern void boss_shot_bulletH011();

void (*boss_shot_bullet[DANMAKU_MAX])() =
{
//中路Boss
	boss_shot_bulletH003,
	boss_shot_bulletH002,
	
//终路Boss
	boss_shot_bulletH001,
	boss_shot_bulletH004,
	boss_shot_bulletH009,
	
//终止

	boss_shot_bulletH000,//防止出现NullPointrException
};