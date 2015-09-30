namespace VGame.Project.SuperComplexWheel.Common
{
    [ProtoBuf.ProtoContract]
    public class Account
    {
        [ProtoBuf.ProtoMember(1)]
        public string Name { get; set; }

        [ProtoBuf.ProtoMember(2)]
        public string Password { get; set; }
        public bool IsPassword(string password)
        {
            return Password == password;
        }
    }
}