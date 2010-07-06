using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms.Design;
using System.Drawing.Design;

using DependencyLibrary;

namespace BoostDependency
{
    /// <summary>
    /// This class describes the properties that are used to configure
    /// the dependency.
    /// </summary>
    [Description("The properties that are used to configure the dependency's build options.")]
    class DependencyDefinition
    {
        //private string svnPath = @"http://svn.boost.org/svn/boost/tags/release/Boost_1_43_0";
        //private string revision = "HEAD";

        //private string localPath = @"c:\boost";

        //// The environment variable that points to the boost root folder.
        //private string environmentVariable = "BOOST_ROOT";

        [Browsable(true)]
        [Category("SVN")]
        [Description("The URL to the subversion depot where you want to retrieve the Boost library")]
        public string SvnPath
        {
            get
            {
                return Properties.Settings.Default.SVN_PATH;
            }

            set
            {
                Properties.Settings.Default.SVN_PATH = value;
            }
        }

        [Browsable(true)]
        [Category("SVN")]
        [Description("The revision you want to retrieve.")]
        [TypeConverter(typeof(SvnRevisionConverter))]
        public string Revision
        {
            get
            {
                return Properties.Settings.Default.SVN_REVISION;
            }
            set
            {
                Properties.Settings.Default.SVN_REVISION = value;
            }
        }

        [Browsable(true)]
        [Category("Local")]
        [Description("The file path on the local machine you want to store the repository.")]
        [Editor(typeof(FolderNameEditor),typeof(UITypeEditor))]
        public string LocalPath
        {
            get
            {
                return Properties.Settings.Default.LOCAL_PATH;
            }

            set
            {
                Properties.Settings.Default.LOCAL_PATH = value;
            }
        }

        [Browsable(true)]
        [Category("Local")]
        [Description("The environment variable that will be used to refer to this dependency source and compiled libraries.")]
        public string EnvironmentVariable
        {
            get
            {
                return Properties.Settings.Default.ENVIRONMENT_VARIABLE;
            }
            set
            {
                Properties.Settings.Default.ENVIRONMENT_VARIABLE = value;
            }
        }
    }
}
