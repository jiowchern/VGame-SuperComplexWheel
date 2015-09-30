namespace VGame.Project.SuperComplexWheel.Common
{
    [ProtoBuf.ProtoContract]
    public enum SYMBOL
    {
        DEF_SYMBOL_00,  // 桃乐斯
        DEF_SYMBOL_01,  // 女巫
        DEF_SYMBOL_02,  // 稻草人
        DEF_SYMBOL_03,  // 铁人
        DEF_SYMBOL_04,  // 狮子
        DEF_SYMBOL_05,  // 狗
        DEF_SYMBOL_06,  // 猴子
        DEF_SYMBOL_07,  // 红鞋
        DEF_SYMBOL_08,  // 龙卷风
        DEF_SYMBOL_09,  // 热气球
        DEF_SYMBOL_10,  // Wild（Bonus）
        DEF_SYMBOL_11,  // Fever
        DEF_SYMBOL_12,	// Free
    }

    public enum SYMBOL_RATIO
    {
        LOSE,
        WINX2,
        WINX3,
        WINX4,
        WINX5,
        MISS
    }
}