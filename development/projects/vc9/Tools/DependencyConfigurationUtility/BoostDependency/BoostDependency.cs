using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

using DependencyLibrary;

namespace BoostDependency
{
    public class BoostDependency : IDependencyItem
    {
        private string name = "Boost";
        private string description = "Boost C++ Libraries";
        private Bitmap icon = Properties.Resources.boost_logo_64x64;
        private Font font = new Font("Candara", 27.75f, FontStyle.Bold);
        private Control control = new BoostDependencyControl();

        public string Name
        {
            get 
            {
                return name;
            }
        }

        public string Description
        {
            get
            {
                return description;
            }
        }

        public Bitmap Icon 
        {
            get 
            {
                return icon;
            }
        }

        public Font Font
        {
            get
            {
                return font;
            }
        }

        public Control Control
        {
            get
            {
                return control;
            }
        }
    }
}
