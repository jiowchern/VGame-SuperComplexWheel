﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using Regulus.Remoting;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Game
{
    public class Verify : IVerify
    {
        public delegate void DoneCallback(Account account);

        public event DoneCallback OnDoneEvent;

        private readonly IAccountFinder _Storage;

        public Verify(IAccountFinder storage)
        {
            _Storage = storage;
        }

        Value<bool> IVerify.Login(string id, string password)
        {
            var returnValue = new Value<bool>();
            var val = _Storage.FindAccountByName(id);
            val.OnValue += account =>
            {
                var found = account != null;
                if (found && account.IsPassword(password))
                {
                    if (OnDoneEvent != null)
                    {
                        OnDoneEvent(account);
                    }

                    returnValue.SetValue(true);
                }
                else
                {
                    returnValue.SetValue(false);
                }
            };
            return returnValue;
        }
    }
}
