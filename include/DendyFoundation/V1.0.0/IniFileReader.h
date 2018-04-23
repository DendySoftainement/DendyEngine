////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////   \file    IniFileReader.h
////   \author  Daniel Huc aka Dendy
////   \date    January 2018
////   -----------------------------
////   \brief   .ini files parser
////   ---------------------------------------------------------------------------------------------------------------------------------------------------------
////   \details Create by passing ini_path or juste use with parse(ini_path) ans then check for (section,key) with isKeyFound()
////            then get the required typed value with a get(). Readable values are of types: [STRING, BOOL, INT or FLOAT]
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//// - Standard includes section - ////
#include <fstream>
#include <string>

//// -Foundation includes section- ////
#include "DendyFoundation/Types.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Specific to 'WINDOWS/LINUX' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#ifdef DENDYENGINE_PLATFORM_WINDOWS

#endif
#ifdef DENDYENGINE_PLATFORM_LINUX

#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// ---- Namespaces ---- ////
namespace DendyEngine {

   namespace DendyFoundation {

      namespace InputOutput {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Class CMyClass                                                                                                                                       ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         class CIniFileReader {

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Members -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
            dyMap<dyPair<dyString, dyString>, dyString> m_stringEntriesMap;
            dyMap<dyPair<dyString, dyString>, dyBool>   m_boolEntriesMap;
            dyMap<dyPair<dyString, dyString>, dyInt>    m_intEntriesMap;
            dyMap<dyPair<dyString, dyString>, dyFloat>  m_floatEntriesMap;

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Methods -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         public:
            //// ----  Object  ---- ////
            CIniFileReader() { /***/ };
            CIniFileReader(dyString iniFilePathStr);
         
         private:
            //// ---- Accessor ---- ////
            dyString	getString(dyString const& a_key)                            const { return m_stringEntriesMap.at(dyPair<dyString, dyString>("", a_key)); }
            dyString	getString(dyString const& a_section, dyString const& a_key) const { return m_stringEntriesMap.at(dyPair<dyString, dyString>(a_section, a_key)); }
            dyBool   getBool(dyString const& a_key)                              const { return m_boolEntriesMap.at(dyPair<dyString, dyString>("", a_key)); }
            dyBool   getBool(dyString const& a_section, dyString const& a_key)   const { return m_boolEntriesMap.at(dyPair<dyString, dyString>(a_section, a_key)); }
            dyInt    getInt(dyString const& a_key)                               const { return m_intEntriesMap.at(dyPair<dyString, dyString>("", a_key)); }
            dyInt    getInt(dyString const& a_section, dyString const& a_key)    const { return m_intEntriesMap.at(dyPair<dyString, dyString>(a_section, a_key)); }
            dyFloat  getFloat(dyString const& a_key)                             const { return m_floatEntriesMap.at(dyPair<dyString, dyString>("", a_key)); }
            dyFloat  getFloat(dyString const& a_section, dyString const& a_key)  const { return m_floatEntriesMap.at(dyPair<dyString, dyString>(a_section, a_key)); }

            //// ----   Core   ---- ////
            dyBool isStringValueFound(dyString const& a_key) const { return m_stringEntriesMap.find(dyPair<dyString, dyString>("", a_key)) != m_stringEntriesMap.end(); }
            dyBool isStringValueFound(dyString const& a_section, dyString const& a_key) const { return m_stringEntriesMap.find(dyPair<dyString, dyString>(a_section, a_key)) != m_stringEntriesMap.end(); }
            dyBool isBoolValueFound(dyString const& a_key) const { return m_boolEntriesMap.find(dyPair<dyString, dyString>("", a_key)) != m_boolEntriesMap.end(); }
            dyBool isBoolValueFound(dyString const& a_section, dyString const& a_key) const { return m_boolEntriesMap.find(dyPair<dyString, dyString>(a_section, a_key)) != m_boolEntriesMap.end(); }
            dyBool isIntValueFound(dyString const& a_key) const { return m_intEntriesMap.find(dyPair<dyString, dyString>("", a_key)) != m_intEntriesMap.end(); }
            dyBool isIntValueFound(dyString const& a_section, dyString const& a_key) const { return m_intEntriesMap.find(dyPair<dyString, dyString>(a_section, a_key)) != m_intEntriesMap.end(); }
            dyBool isFloatValueFound(dyString const& a_key) const { return m_floatEntriesMap.find(dyPair<dyString, dyString>("", a_key)) != m_floatEntriesMap.end(); }
            dyBool isFloatValueFound(dyString const& a_section, dyString const& a_key) const { return m_floatEntriesMap.find(dyPair<dyString, dyString>(a_section, a_key)) != m_floatEntriesMap.end(); }
            dyBool isValueFound(dyString const& a_key);
            dyBool isValueFound(dyString const& a_section, dyString const& a_key);
            void parse(dyString a_iniFilePath);

         };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                        ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      }
   }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
