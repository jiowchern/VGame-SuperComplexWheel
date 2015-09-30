namespace VGame.Project.SuperComplexWheel.Common
{
    /// <summary>
    /// 轉輪結果
    /// </summary>
    [ProtoBuf.ProtoContract]
    public struct SpinResult
    {
        /// <summary>
        /// 取得的符號
        /// </summary>
        [ProtoBuf.ProtoMember(1)]
        public SYMBOL[] Symbols;

        /// <summary>
        /// 彩金分数
        /// </summary>
        [ProtoBuf.ProtoMember(2)]
        public int Score;

        /// <summary>
        /// 预期中奖分数
        /// </summary>
        [ProtoBuf.ProtoMember(3)]
        public int ExpectedScore;
    }
}