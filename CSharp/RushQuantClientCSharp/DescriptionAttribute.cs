using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace RushQuant.Clients
{
    public class DescriptionAttribute : Attribute
    {
        public static Dictionary<int, string> GetDescriptions<T>()
        {
            Dictionary<int, string> items = new Dictionary<int, string>();
            FieldInfo[] fields = typeof(T).GetFields(BindingFlags.Static | BindingFlags.Public);
            foreach (FieldInfo field in fields)
            {
                int value = (int)field.GetValue(null);
                DescriptionAttribute attribute = ((DescriptionAttribute)Attribute.GetCustomAttribute(field, typeof(DescriptionAttribute)));
                if (attribute != null)
                {
                    items.Add(value, $"{value}-{attribute.Description}");
                }
            }
            return items;
        }

        private string _description;
        public string Description
        {
            get
            {
                return this._description;
            }
        }

        public DescriptionAttribute(string description)
        {
            this._description = description;
        }
    }
}
