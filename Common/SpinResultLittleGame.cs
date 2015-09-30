namespace VGame.Project.SuperComplexWheel.Common
{
    [ProtoBuf.ProtoContract]
    public struct SpinResultLittleGame
    {
        /// <summary>
        /// 取得的符號
        /// </summary>
        [ProtoBuf.ProtoMember(1)]
        public SYMBOL Symbol;        

        /// <summary>
        /// 预期中奖分数
        /// </summary>
        [ProtoBuf.ProtoMember(2)]
        public int ExpectedScore;
    }
}