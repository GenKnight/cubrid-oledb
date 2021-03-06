/*
 * Copyright (C) 2008 Search Solution Corporation. All rights reserved by Search Solution. 
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met: 
 *
 * - Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer. 
 *
 * - Redistributions in binary form must reproduce the above copyright notice, 
 *   this list of conditions and the following disclaimer in the documentation 
 *   and/or other materials provided with the distribution. 
 *
 * - Neither the name of the <ORGANIZATION> nor the names of its contributors 
 *   may be used to endorse or promote products derived from this software without 
 *   specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE. 
 *
 */

#pragma once

class CTableConstraintsRow
{
public:
	WCHAR m_szConstraintCatalog[1];
	WCHAR m_szConstraintSchema[1];
	WCHAR m_szConstraintName[30];
	WCHAR m_szTableCatalog[1];
	WCHAR m_szTableSchema[1];
	WCHAR m_szTableName[256];
	WCHAR m_szConstraintType[12];
	VARIANT_BOOL m_bIsDeferrable;
	VARIANT_BOOL m_bInitiallyDeferred;
	WCHAR m_szDescription[1];
	
	CTableConstraintsRow()
	{
		m_szConstraintCatalog[0] = NULL;
		m_szConstraintSchema[0] = NULL;
		m_szConstraintName[0] = NULL;
		m_szTableCatalog[0] = NULL;
		m_szTableSchema[0] = NULL;
		m_szTableName[0] = NULL;
		m_szConstraintType[0] = NULL;
		m_szDescription[0] = NULL;
		m_bIsDeferrable = VARIANT_FALSE;
		m_bInitiallyDeferred = VARIANT_FALSE;
	}

BEGIN_PROVIDER_COLUMN_MAP(CTableConstraintsRow)
	PROVIDER_COLUMN_ENTRY_WSTR("CONSTRAINT_CATALOG", 1, m_szConstraintCatalog)
	PROVIDER_COLUMN_ENTRY_WSTR("CONSTRAINT_SCHEMA", 2, m_szConstraintSchema)
	PROVIDER_COLUMN_ENTRY_WSTR("CONSTRAINT_NAME", 3, m_szConstraintName)
	PROVIDER_COLUMN_ENTRY_WSTR("TABLE_CATALOG", 4, m_szTableCatalog)
	PROVIDER_COLUMN_ENTRY_WSTR("TABLE_SCHEMA", 5, m_szTableSchema)
	PROVIDER_COLUMN_ENTRY_WSTR("TABLE_NAME", 6, m_szTableName)
	PROVIDER_COLUMN_ENTRY_WSTR("CONSTRAINT_TYPE", 7, m_szConstraintType)
	PROVIDER_COLUMN_ENTRY_TYPE_PS("IS_DEFERRABLE", 8, DBTYPE_BOOL, 0xFF, 0xFF, m_bIsDeferrable)
	PROVIDER_COLUMN_ENTRY_TYPE_PS("INITIALLY_DEFERRED", 9, DBTYPE_BOOL, 0xFF, 0xFF, m_bInitiallyDeferred)
	PROVIDER_COLUMN_ENTRY_WSTR("DESCRIPTION", 10, m_szDescription)
END_PROVIDER_COLUMN_MAP()
};

class CSRTableConstraints :
	public CSchemaRowsetImpl<CSRTableConstraints, CTableConstraintsRow, CCUBRIDSession>
{
public:
	SR_PROPSET_MAP(CSRTableConstraints)

	HRESULT Execute(LONG* pcRowsAffected, ULONG cRestrictions, const VARIANT *rgRestrictions);
	DBSTATUS GetDBStatus(CSimpleRow*, ATLCOLUMNINFO* pInfo);
	HRESULT FillRowData(int hReq, UINT uCodepage, LONG* pcRowsAffected, const char *table_name, int constraint_type);
};

