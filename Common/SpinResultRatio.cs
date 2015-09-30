namespace VGame.Project.SuperComplexWheel.Common
{

    [ProtoBuf.ProtoContract]
    public struct SpinResultRatio
    {

        /// <summary>
        /// 比倍符號
        /// </summary>
        [ProtoBuf.ProtoMember(1)]
        public SYMBOL_RATIO Symbol;
        /// <summary>
        /// 预期中奖分数
        /// </summary>
        [ProtoBuf.ProtoMember(2)]
        public int ExpectedScore;
    }
}