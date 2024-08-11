# MFC_Practice
this is mfc practice repository

과제 : 다이얼로그 창

1. 에디터박스, 버튼 구성
2. 버튼눌러서 폴더선택
3. 폴더경로가 에디터박스에 출력되게
4. 그 밑에 해당폴더 파일의 리스트가 나오도록

> 개념

1. CFolderPickerDialog : 폴더선택 클래스
2. CFileFind : 경로를 매개변수로 넣어주면 경로안의 파일을 출력할수 있는 클래스

```c++
void CMFCSelectFolderDlg::OnBnClickedButtonBrowse()
{
	CFolderPickerDialog dlgFolder(NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, this);

	if (dlgFolder.DoModal() == IDOK)
	{
		strPath = dlgFolder.GetPathName();
		UpdateData(FALSE);

		listFiles.ResetContent();

		CFileFind finder;
		CString strWildcard = strPath + _T("\\*.*");
		
		BOOL bWorking = finder.FindFile(strWildcard);
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			listFiles.AddString(finder.GetFileName());
		}
	}
}
```


https://github.com/user-attachments/assets/0548a55f-c9c1-4604-8d5f-1a5f76cdbbd2

