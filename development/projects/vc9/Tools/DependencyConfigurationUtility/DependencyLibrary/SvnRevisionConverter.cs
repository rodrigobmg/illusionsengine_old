using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Collections;

namespace DependencyLibrary
{
    /// <summary>
    /// A type converter that displays a drop-down box that contains all of the revisions
    /// for a particular SVN path.
    /// </summary>
    public class SvnRevisionConverter : StringConverter
    {

        private ArrayList revisions = new ArrayList();

        public SvnRevisionConverter() : base()
        {
            // Add a default value to our revisions array.
            revisions.Add("HEAD");
        }

        public override bool GetStandardValuesSupported(ITypeDescriptorContext context )        {
            return true;        }

        public override StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
        {
            return new StandardValuesCollection(revisions);
        }
    }
}
