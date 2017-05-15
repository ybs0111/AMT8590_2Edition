#ifndef _TIPSWARE_BUTTON_DIB_STATIC_H_
#define _TIPSWARE_BUTTON_DIB_STATIC_H_

// +------------------------------------------------+
// |  Object Name :  TipsWare Normal Static Control |
// +------------------------------------------------+
//
//  Microsoft Windows���� �����ϴ� �⺻���� Static ��Ʈ���� SubClassing �ϰų� ���� �����Ͽ�
//  ������ �����̳�, ���ڿ��� ���� �Ǵ� ���ڿ��� ��Ʈ�� ���� �����Ҽ� �ֵ��� ������ ��Ʈ���Դϴ�. 
//
//   ���� ������ : �輺��.
//   ���� ������ : �輺��.              2000�� 3�� 13��
// ------------------------------------------------------
//        ������ : �輺��.              2000�� 3�� 14��
//          ���� : �Լ����� ���� �߰�.
// ------------------------------------------------------

// Normal Static ��Ʈ���� Subclassing ���� ���� �����Ͽ� ����ϰ��� �ϴ� ��쿡 ����ϴ� �Լ��̴�.
// 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. const char *parm_text
//    Static ��Ʈ�ѿ� ����� ���ڿ��� �Է��Ѵ�. 
// 2. int parm_style
//    Static ��Ʈ���� �Ӽ�(��/�� ����, ��/���� ����...)�� �����Ѵ�.
// 3. CRect parm_rect
//    ������ ��Ʈ���� ��ġ ��ǥ.
// 4. CWnd *parm_parent
//    ������ ��Ʈ���� ������ �������� ������.
// 5. int parm_id
//    ������ ��Ʈ���� ��Ʈ�� ID.
//
// �� �Լ��� CWnd *�� ��ȯ�ϴµ�, �� ���� ���������� ������ Normal Static ��Ʈ�� ��ü�� �ּ��̴�. �� ��ü�� new �����ڸ�
// ����Ͽ� �������� �����Ǳ� ������ �Ѱ� ���� �ּҰ��� ������ѳ��Ҵٰ� �ݵ�� delete�ؾ� �Ѵ�. delete�ÿ��� Ư����
// �������̽��� ����� �ʿ���� ����ϰ� �ִ� �ش� �����͸� ���� delete��Ű�� �ȴ�. 
CWnd *CreateStaticObject(const char *, int , CRect , CWnd *, int );

CWnd *CreateStaticObjectEx(const char *parm_text, int parm_style, int parm_style_ex, CRect parm_rect, CWnd *parm_parent, int parm_id);

// �Ϲ� Static ��Ʈ���� Subclassing�Ͽ� Normal Static ��Ʈ���� �����ϴ� �Լ��̴�.
// 2���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. int parm_ctrl_id
//    Subclassing �� Static ��Ʈ���� Resource ID.
// 2. CWnd *parm_parent
//    Subclassing �� Static ��Ʈ���� �����ϴ� �������� ������.
//
// �� �Լ��� CWnd *�� ��ȯ�ϴµ�, �� ���� ���������� ������ Normal Static ��Ʈ�� ��ü�� �ּ��̴�. �� ��ü�� new �����ڸ�
// ����Ͽ� �������� �����Ǳ� ������ �Ѱ� ���� �ּҰ��� ������ѳ��Ҵٰ� �ݵ�� delete�ؾ� �Ѵ�. delete�ÿ��� Ư����
// �������̽��� ����� �ʿ���� ����ϰ� �ִ� �ش� �����͸� ���� delete��Ű�� �ȴ�. 
CWnd *CreateSubClassingStaticObject(int , CWnd *);


// ������ Normal Static ��Ʈ�ѿ� �Ʒ��� ������ �Ӽ��� �����ϰ��� �ϴ� �Լ��̴�.
// �� 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. CWnd *parm_object
//    �Ӽ��� �����ϰ��� �ϴ� Normal Static ��Ʈ���� �ּ������̴�.
// 2. int parm_id
//    � �Ӽ��� ���������� ����. ���� ������ �Ӽ��� ������ �Լ� ������ ���� �Ŀ� ������ ����.
// 3. void *parm_property
//    �������� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 4. int parm_data1
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 5. int parm_data2
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
int SetStaticOneProperty(CWnd *, int , void *, int , int );
// SetStaticOneProperty�Լ��� 2��° ������ parm_id�� ���� ���� 3~5�� ���޵Ǵ� ������ �����ȴ�. ���� ID�� ���� 
// �ʿ� ������ ��Ȯ���� ������ ������ �ʴ� ������ ��Ȳ�� �߻��Ҽ� �ִ�. ���� ������ �Ӽ��� �� 7�����̰� �������
// ������ �����ϴ� �Լ��� �ϳ� �����Ͽ� �� 8������ ID�� �����ȴ�. ������ �ǹ̿� ������ ������ ����.
   #define TS_SET_COLOR                 1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_SET_COLOR�� Static ��Ʈ�ѿ� ���Ե� �ý�Ʈ ������ �����ϴ� ����� �Ѵ�. 3��°�� 4��° ���ڿ� ���ϴ� ���� �־��ָ� �ȴ�.
// ���⼭ ���� �� ���� parm_property�� NULL�̸� parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property��
// ������ ������ �Լ��� �����Ѵ�.
// COLORREF temp_color = RGB(0, 0, 255);
// SetStaticOneProperty(object_pointer, TS_SET_COLOR, &temp_color, 0, 0);
//                               �Ǵ�
// SetStaticOneProperty(object_pointer, TS_SET_COLOR, NULL, RGB(0, 0, 255), 0);
   #define TS_SET_WINDOW_TEXT           2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_SET_WINDOW_TEXT�� Static ��Ʈ�ѿ� ���Ե� �ý�Ʈ ������ �����ϴ� ����� �Ѵ�. 3��° ���ڿ� ���ϴ� ���ڿ��� �ּҸ� 
// �־��ָ� �ȴ�.
// CString my_string = "Hello My Control";
// SetStaticOneProperty(object_pointer, TS_SET_WINDOW_TEXT, (const char *)my_string, 0, 0);
//                               �Ǵ�
// SetStaticOneProperty(object_pointer, TS_SET_WINDOW_TEXT, "Hello My Control", 0, 0);
   #define TS_SET_FONT                  3
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_SET_FONT�� Static ��Ʈ�ѿ� �ܺο��� ������ ��Ʈ ��ü ������ ���� �����ϴ� ����� �Ѵ�. ���� ���������� �����ߴ�
// ��Ʈ ��ü ������ ���ŵǰ� ����ڰ� ������ ��Ʈ ��ü ������ ����Ѵ�. ��, �ܺο��� ���޵Ǵ� ��Ʈ ��ü�� ���Ӽ��� ������
// �־�߸� �Ѵ�. ���� ���, ���������� ����� ��Ʈ ��ü�� �ּҸ� �Ҵ��ϴ� ��� Static ��Ʈ�ѿ� ������ �����. ���� 
// �ܺο��� �����Ǿ� ���޵Ǵ� ��Ʈ ��ü�� �ּ��� Static ��Ʈ���� Life Time���ٴ� ���� �Ѵ�.
// CFont m_font;   <--  ��� ���� �Ǵ� ���� ����
// m_font.CreateFont.....
// SetStaticOneProperty(object_pointer, TS_SET_FONT, &m_font, 0, 0);
   #define TS_CHANGE_FONT               4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_CHANGE_FONT�� Static ��Ʈ�ѿ��� ����ϴ� ��Ʈ ��ü ������ �����Ѵ�. ����, ������ ������ ��Ʈ ��ü ������ �ִٸ� �����ϰ�
// �ܺο��� ������ ��Ʈ ��ü ������ �ִٸ� �ش� ������ ������� �ʵ��� ������ ������.
// �� ��쿡�� 3~5 ���ڰ� ��� ���Ǹ� ������ �ǹ̴� ������ ����.
// (3, parm_property) : ����ϰ��� �ϴ� ��Ʈ�� �̸�
// (4, parm_data1)    : ��Ʈ�� ������ �Ӽ��� ����� ���ΰ��� ����. (1�̸� ���, 0�Ƹ� ��� ����.)
// (5, parm_data2)    : ��Ʈ�� ũ�⸦ �����Ѵ�.  �⺻ ũ��� 12�� �����Ѵ�.
// ����ü�� ����ϰ� ũ�Ⱑ 12�̸� ���� �Ӽ��� ���� ��Ʈ�� ����ϰ� �ʹٸ� �Ʒ��� ���� �����ϸ� �ȴ�.
// SetStaticOneProperty(object_pointer, TS_CHANGE_FONT, "����ü", 1, 12);
   #define TS_SET_TRANSPARENT_MODE      5
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_SET_TRANSPARENT_MODE�� Static ��Ʈ���� ����� �����ϰ� ����� �������� �����Ѵ�. 3��° �Ǵ� 4��° ���ڸ� �̿��� �� �ְ�
// �ش� ���� 1�̸� ����� �����ϰ� ����ϰ� 0�̸� ������ �������� ����Ѵ�. ���⼭ ���� �� ���� parm_property�� NULL�̸�
// parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property�� ������ ������ �Լ��� �����Ѵ�.
// char temp_flag = 1;
// SetStaticOneProperty(object_pointer, TS_SET_TRANSPARENT_MODE, &temp_flag, 0, 0);
//                               �Ǵ�
// SetStaticOneProperty(object_pointer, TS_SET_TRANSPARENT_MODE, NULL, 1, 0);
// Normal Static ��Ʈ���� �⺻������ ����� �����ϰ� �ϴ� �Ӽ��� ������ �ֱ� ������ ó�� �����ɶ� ������ ������ �����̴�.
// �׸��� 3��° ���ڸ� �̿��ϴ� ��� ����ϴ� ������ �ݵ�� char���̿��� �Ѵ�.
   #define TS_SET_MULTI_LINE_MODE       6
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_SET_MULTI_LINE_MODE�� Static ��Ʈ�ѿ� ���ڿ��� ����(Multi-Line)���� ǥ���� ���ΰ��� �����Ѵ�. 3��° �Ǵ� 4��° ���ڸ� 
// �̿��� �� �ְ� �ش� ���� 1�̸� �������� ����ϰ� 0�̸� �������� ����Ѵ�. ���⼭ ���� �� ���� parm_property�� NULL�̸�
// parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property�� ������ ������ �Լ��� �����Ѵ�.
// char temp_flag = 1;
// SetStaticOneProperty(object_pointer, TS_SET_MULTI_LINE_MODE, &temp_flag, 0, 0);
//                               �Ǵ�
// SetStaticOneProperty(object_pointer, TS_SET_MULTI_LINE_MODE, NULL, 1, 0);
// Normal Static ��Ʈ���� �⺻������ ����(Single-Line) �Ӽ��� ������ �ִ�. �׸��� 3��° ���ڸ� �̿��ϴ� ��� ����ϴ�
// ������ �ݵ�� char���̿��� �Ѵ�.
   #define TS_SET_BK_COLOR              7
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_SET_BK_COLOR�� Static ��Ʈ�ѿ� ������ �����ϴ� ����� �Ѵ�. 3��° �Ǵ� 4��° ���ڸ� �̿��� �� �ְ� 
// parm_property�� NULL�̸� parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property�� ������ ������ �Լ���
// �����Ѵ�. ���� �� �Ӽ��� ����� �������� �ʴٰ� ������ ��쿡�� �Ӽ��� ��ȿ�ϴ�.
// COLORREF temp_color = RGB(0, 0, 255);
// SetStaticOneProperty(object_pointer, TS_SET_BK_COLOR, &temp_color, 0, 0);
//                               �Ǵ�
// SetStaticOneProperty(object_pointer, TS_SET_BK_COLOR, NULL, RGB(0, 0, 255), 0);
   #define TS_SET_TEXT_REVISION         8
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_SET_TEXT_REVISION�� Static ��Ʈ���� �ؽ�Ʈ ���ڿ��� ��ġ�� ���� ����� �Ѵ�. 4��° �� 5��° ���ڸ� �̿��� ��
// �ְ� parm_data1�� ���� ���ڿ��� ��ġ�� X ��ǥ, parm_data2�� ���� ���ڿ��� ��ġ�� Y ��ǥ�� �����Ѵ�.
// SetStaticOneProperty(object_pointer,TS_SET_TEXT_REVISION,NULL,7,2);
   #define TS_UPDATE_OBJECT             9
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_UPDATE_OBJECT�� Static ��Ʈ�ѿ� Ư�� �Ӽ��� �����ϴ� ����� ����. ���� ������ ������ �Ӽ����� ����� ��,
// ����� ������ ȭ������ ������ �Ҷ�, ��ü�� ������ ȭ���� ���Ž�Ű�� ����� ������ �ִ�. �׸��� ���ڴ� ������� �ʴ´�.
// SetStaticOneProperty(object_pointer, TS_UPDATE_OBJECT, NULL, 0, 0);


// ������ Normal Static ��Ʈ�ѿ� �Ʒ��� ������ �Ӽ��� � ���� �����Ǿ� �ִ��� �˰��� �ϴ� ��쿡 ����ϴ� �Լ��̴�.
// �� 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. CWnd *parm_object
//    �Ӽ��� �˰��� �ϴ� Normal Static ��Ʈ���� ������.
// 2. int parm_id
//    � �Ӽ��� �˾Ƴ� �������� ����. ���� ������ �Ӽ��� ������ �Լ� ������ ���� �Ŀ� ������ ����.
// 3. void *parm_property
//    �������� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 4. int parm_data1
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 5. int parm_data2
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
int GetStaticOneProperty(CWnd *, int , void *, int , int );
// GetStaticOneProperty�Լ��� 2��° ������ parm_id�� ���� ���� 3~5�� ���޵Ǵ� ������ �����ǰ� �ڽ��� ����� �ϴ� ������
// �����ȴ�. ���� ID�� �߸� �����ϰų� ID�� ���� �ʿ� ������ ��Ȯ���� ������ ������ �ʴ� ���� ������ ��ȯ�� ���� �ִ�.
// �� ��Ʈ�� ��ü�� �����ϴ� ������ �Ʒ��� ���� ��� 5���̸� ������ ������ ������ ����.
// ������ ���� �� �Լ��� �������� �뵵�� ����Ǿ��� ������ ��ɿ� ���� ������ ĳ����(Casting)�ؼ� ����ؾ� �Ѵ�.
   #define TS_GET_COLOR                 1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_GET_COLOR�� Static ��Ʈ�ѿ� ���Ե� �ý�Ʈ ������ �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰� ������ ��ȯ�Ǵ� ���� COLORREF���̴�.
// COLORREF static_color = (COLORREF)GetStaticOneProperty(object_pointer, TS_GET_COLOR, NULL, 0, 0);
   #define TS_GET_WINDOW_TEXT           2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_GET_WINDOW_TEXT�� Static ��Ʈ�ѿ� ���Ե� �ý�Ʈ�� ������ �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰� ������ ��ȯ�Ǵ� ����
// ���ڿ��� �����ּ��̴�. ��, const char * �Ǵ� char * ���̴�.
// const char *p_text = (const char *)GetStaticOneProperty(object_pointer, TS_GET_WINDOW_TEXT, NULL, 0, 0);
   #define TS_GET_TRANSPARENT_MODE      3
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_GET_TRANSPARENT_MODE�� Static ��Ʈ���� ����� �����ϰ� �����Ǿ��ִ����� �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰� ������
// ��ȯ�Ǵ� ���� char ���̴�. ��ȯ���� 0�̸� �������� ���� �����̰� 1�̸� ����� ������ �����̴�.
// char static_transparent_flag = (char)GetStaticOneProperty(object_pointer, TS_GET_TRANSPARENT_MODE, NULL, 0, 0);
   #define TS_GET_MULTI_LINE_MODE       4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_GET_MULTI_LINE_MODE�� Static ��Ʈ���� ����(Multi-Line)�� �����ϵ��� �����ִ����� �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰�
// ������ ��ȯ�Ǵ� ���� char ���̴�. ��ȯ���� 0�̸� ����(Single-Line)�����̰� 1�̸� ����(Multi-Line) �����̴�.
// char static_transparent_flag = (char)GetStaticOneProperty(object_pointer, TS_GET_MULTI_LINE_MODE, NULL, 0, 0);
   #define TS_GET_BK_COLOR              5
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TS_GET_BK_COLOR�� Static ��Ʈ�ѿ� ���Ե� �ý�Ʈ�� ��� ������ �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰� ������ ��ȯ�Ǵ� ����
// COLORREF���̴�. �׸��� �� ���� ������ �������� �ʴٰ� ����� ��쿡�� ��ȿ�ϴ�.
// COLORREF static_color = (COLORREF)GetStaticOneProperty(object_pointer, TS_GET_BK_COLOR, NULL, 0, 0);

// +------------------------------------------------+
// |  Object Name :  TipsWare Normal DIB Control    |
// +------------------------------------------------+
//
//  Microsoft Windows���� �����ϴ� DIB(device-independent bitmap) �������� ������ ���Ͽ��� �̹��� ������ �о
//  ����ڰ� ������ ��ġ�� ����Ѵ�.
//
//   ���� ������ : �輺��.
//   ���� ������ : �輺��.              2000�� 3�� 13��
// ------------------------------------------------------
//        ������ : �輺��.              2000�� 3�� 14��
//          ���� : �Լ����� ���� �߰�.
// ------------------------------------------------------

// DIB������ ���Ͽ��� �̹����� �о� �鿩�� ������ ��ü�� �����ϰ� ������ ��ο��� �̹��� ������ �о�´�.
// �� �Լ��� 1���� ���ڸ� ������ �� ������ ������ ����.
// 1. const char *parm_pathname
//    ������ ���ÿ� �о�� DIB ��θ� �����Ѵ�. ���� ��ü�� �ܼ��� �����ϰ� �ʹٸ� NULL �Ǵ� ""�̶�� ������ �ȴ�.
//
// �� �Լ��� char *�� ��ȯ�ϴµ�, �� ���� ���������� ������ DIB ��Ʈ�� ��ü�� �ּ��̴�. �� ��ü�� new �����ڸ�
// ����Ͽ� �������� �����Ǳ� ������ �Ѱ� ���� �ּҰ��� ������ѳ��Ҵٰ� �ݵ�� delete�ؾ� �Ѵ�. ������ �� ��Ʈ���� ��ü �ּ�
// ������ ���ؼ� �������� �̿����� ���ϱ� ������ delete �����ڸ� ���������� ����ϸ� �ȵǰ� �ش� ��Ʈ���� �����ϴ�
// DeleteDibObject�̶�� �Լ��� ȣ���Ͽ� �����ؾ߸� �Ѵ�.
char *CreateDibObject(const char *);


// ����ϴ� DIB ��Ʈ�� ��ü�� �����ϰ��� �ϴ� ��쿡 �� �Լ��� ȣ���Ѵ�.
// �� �Լ��� 1���� ���ڸ� ������ �� ������ ������ ����.
// 1. char *parm_object
//    �����ϰ��� �ϴ� DIB ��Ʈ���� �ּ������̴�.
void DeleteDibObject(char *);


// ����ڰ� DIB �̹��� ��ü�� ������ �׸��� ����ڰ� ������ ��ġ�� �ٵ��� �������� ����Ѵ�.
// �� �Լ��� 3���� ���ڸ� ������ ������ �ǹ̴� ������ ����.
// 1. char *parm_object
//    ����� �̹����� �����ϰ� �ִ� ��ü�� �ּ������̴�.
// 2. CDC *parm_dc
//    �̹����� ����� DC(Display/Device Context)�� ������ �����Ѵ�.
// 3. CRect parm_rect
//    �̹����� ����� ��ǥ.. �о���� �̹������� ������ ��ǥ�� ũ�� �ٵ��� �������� ä��⸦ �õ��Ѵ�.
char DrawBackgroundImage(char *, CDC *, CRect );


// ���� ��ü�� �о���� �̹��� ������ ����ڰ� ���ϴ� ��ġ�� ����Ѵ�. ��� ũ�⳪, ���� ���ſ� ���� ����� 
// SetDibOneProperty�� ���ؼ� �����ϰ� ���⿡���� �ܼ��� ��� ��ġ�� �����ϸ� �ȴ�. �� �Լ��� 4���� ���ڸ� ������ ������
// �ǹ̴� ������ ����.
// 1. char *parm_object
//    ����� �̹����� �����ϰ� �ִ� ��ü�� �ּ������̴�.
// 2. CDC *parm_dc
//    �̹����� ����� DC(Display/Device Context)�� ������ �����Ѵ�.
// 3. int parm_x
//    �̹����� ����� X�� ��ǥ�� �����Ѵ�.
// 3. int parm_y
//    �̹����� ����� Y�� ��ǥ�� �����Ѵ�.
void ShowDibImage(char *, CDC *, int , int );

char ShowDibImageEx(char *parm_object, CDC *parm_dc, int parm_x, int parm_y);
char ShowDibImageExNoPosition(char *parm_object, CDC *parm_dc);

// ������ DIB ��Ʈ�ѿ� �Ʒ��� ������ �Ӽ��� �����ϰ��� �ϴ� �Լ��̴�.
// �� 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. CWnd *parm_object
//    �Ӽ��� �����ϰ��� �ϴ� DIB ��Ʈ���� �ּ������̴�.
// 2. int parm_id
//    � �Ӽ��� ���������� ����. ���� ������ �Ӽ��� ������ �Լ� ������ ���� �Ŀ� ������ ����.
// 3. void *parm_property
//    �������� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 4. int parm_data1
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 5. int parm_data2
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
int SetDibOneProperty(char *, int , void *, int , int );
// SetDibOneProperty�Լ��� 2��° ������ parm_id�� ���� ���� 3~5�� ���޵Ǵ� ������ �����ȴ�. ���� ID�� ���� 
// �ʿ� ������ ��Ȯ���� ������ ������ �ʴ� ������ ��Ȳ�� �߻��Ҽ� �ִ�. ���� ������ �Ӽ��� �� 5�����̴�. �׸���
// ������ �ǹ̿� ������ ������ ����.
   #define TD_SET_DIB                   1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TD_SET_DIB�� ������ DIB ���Ͽ��� �׸� ������ �о���̴� ����� �Ѵ�. 3��°���ڿ� �а��� �ϴ� ������ ��θ� �����ָ� �ȴ�.
// CString my_path = "my_image.bmp";
// int ret = SetDibOneProperty(object_pointer, TD_SET_DIB, (const char *)my_path, 0, 0);
//                               �Ǵ�
// int ret = SetDibOneProperty(object_pointer, TD_SET_DIB, "my_image.bmp", 0, 0);
// ���Լ��� �ϳ��� int ��ȯ���� �����µ� 1�̸� ���������� ������ ��� �����͸� �о� ���ΰ��̸� -1�̸� �׸� ���� �б⿡
// ������ ���̴�.
   #define TD_SET_DIB_DLG               2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TD_SET_DIB_DLG�� ������ DIB ���Ͽ��� �׸� ������ �о���̴� ����� �Ѵ�. ������ TD_SET_DIB�ʹ� �޸� �������� ������ ������
// ��θ� ������� �ʰ� �Լ����� �����ϴ� ���Ͽ��� ��ȭ���ڸ� �̿��Ͽ� �׸� ������ �����Ѵ�. ���� ���ڸ� �̿����� �ʴ´�.
// int ret = SetDibOneProperty(object_pointer, TD_SET_DIB_DLG, NULL, 0, 0);
// ���Լ��� �ϳ��� int ��ȯ���� �����µ� 1�̸� ���������� ������ ��� �����͸� �о� ���ΰ��̰� -1�̸� �׸� ���� �б⿡
// ������ ���̸� 0�̸� ���Ͽ��� ��ȭ���ڿ��� ��ҹ�ư�� ������ ����̴�.
   #define TD_SET_FIX_SIZE              3
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TD_SET_FIX_SIZE�� �о���� �׸������� ����Ҷ� � ũ��� ����Ұ������� �����Ѵ�. �� �Լ��� ���޵� �Ű����� ��������
// ��� ũ��� �����ϰ� �׸��� ����Ѵ�. �������, ����/���ΰ� 30/40�̸� ���δ� 30 pixelũ��� ��µǰ� ���δ� 40 pixelũ���
// ��µȴ�. �� �Լ��� ���� �����ϱ� ���ؼ� 4~5��° �Ű������� �̿��Ѵ�.
// (4, parm_data1)    : ����� �׸��� x�� ���� ũ��
// (5, parm_data2)    : ����� �׸��� y�� ���� ũ��
// SetDibOneProperty(object_pointer, TD_SET_FIX_SIZE, NULL, 30, 40);
// �׸��� �о���� ��, �׸��� �⺻ ��� ũ��� �׸��� ���� ũ���̴�.
   #define TD_SET_RATE_SIZE             4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TD_SET_RATE_SIZE�� �о���� �׸������� ����Ҷ� � ũ��� ����Ұ������� �����Ѵ�. �� �Լ��� ���޵� �Ű����� �������
// ��� ũ��� �����ϰ� �׸��� ����Ѵ�. �������, ����/���ΰ� 2/1.5�̸� ���δ� �о���� �׸��� �⺻ ũ���� 2���̰� ���δ�
// �׸� �⺻ ũ���� 1.5��� ���� ����Ѵ�. �� �Լ��� ���� �����ϱ� ���ؼ� 3��° �Ű��������� �̿��Ѵ�. ������ ������ ����
// ������ �Ǽ� ���̱� ������ 4~5��° �Ű������� �̿��ϱ� ��Ʊ� ������ 3��° �Ű������� double �迭�� �����Ͽ� x, y����
// ��� �����Ѵ�.
// double pos[2] = { double(2), double(1.5) };
// SetDibOneProperty(object_pointer, TD_SET_RATE_SIZE, pos, 0, 0);
// �׸��� �о���� ��, �׸��� �⺻ ��� ũ��� �׸��� ���� ũ���̴�.
   #define TD_SET_TRANSPARENT_MODE      5
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TD_SET_TRANSPARENT_MODE�� �о���� �׸������� ����Ҷ� �׸��� Ư�� ���� �Ѱ����� �����ϰ������ �������� �����Ѵ�.
// (4, parm_data1)    : ���� ��� ���� ����� ����Ұ������� �����Ѵ�. 1�̸� ����ϰ� 0�̸� ������.
// (5, parm_data2)    : parm_data1�� 1�� ��쿡�� ��ȿ�ϸ�, ������ ������ �����ϸ� �ȴ�.
// ���� ���� ����� ����Ͽ� RGB(0, 0, 255)�� �ش��ϴ� ������ �����ϴ� ���� �Ʒ��� �����ϸ� �ȴ�.
// SetDibOneProperty(object_pointer, TD_SET_TRANSPARENT_MODE, NULL, 1, RGB(0, 0, 255));
// �׸��� ���� ���� ����� ������� �ʴ� ��쿡�� �Ʒ��� �����ϸ� �ȴ�.
// SetDibOneProperty(object_pointer, TD_SET_TRANSPARENT_MODE, NULL, 0, 0);
   #define TD_SET_DRAW_POSITION         6
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ������ DIB ��Ʈ�ѿ� �Ʒ��� ������ �Ӽ��� � ���� �����Ǿ� �ִ��� �˰��� �ϴ� ��쿡 ����ϴ� �Լ��̴�.
// �� 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. CWnd *parm_object
//    �Ӽ��� �˰��� �ϴ� DIB ��Ʈ���� ������.
// 2. int parm_id
//    � �Ӽ��� �˾Ƴ� �������� ����. ���� ������ �Ӽ��� ������ �Լ� ������ ���� �Ŀ� ������ ����.
// 3. void *parm_property
//    �������� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 4. int parm_data1
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 5. int parm_data2
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
int GetDibOneProperty(char *, int , void *, int , int );
// GetStaticOneProperty�Լ��� 2��° ������ parm_id�� ���� ���� 3~5�� ���޵Ǵ� ������ �����ǰ� �ڽ��� ����� �ϴ� ������
// �����ȴ�. ���� ID�� �߸� �����ϰų� ID�� ���� �ʿ� ������ ��Ȯ���� ������ ������ �ʴ� ���� ������ ��ȯ�� ���� �ִ�.
// �� ��Ʈ�� ��ü�� �����ϴ� ������ �Ʒ��� ���� ��� 5���̸� ������ ������ ������ ����.
// ������ ���� �� �Լ��� �������� �뵵�� ����Ǿ��� ������ ��ɿ� ���� ������ ĳ����(Casting)�ؼ� ����ؾ� �Ѵ�.
   #define TD_GET_DIB_SIZE              1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TD_GET_DIB_SIZE�� �о���� �׸��� ���� ũ�⸦ �˰��� �ϴ� ��쿡 ���ȴ�. Ư���� �Ű������� ������� ������ ��ȯ�Ǵ�
// ���� CSize *���̴�.
// CSize *p_size = (CSize *)GetDibOneProperty(object_pointer, TD_GET_DIB_SIZE, NULL, 0, 0);
   #define TD_GET_DIB_HANDLE            2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TD_GET_DIB_HANDLE�� �о���� �׸������� ������ �޸��� Handle�� ����� �ϴ� ��쿡 ���ȴ�. ��ȯ���� HANDLE���̴�.
// HANDLE h_dib = (HANDLE)GetDibOneProperty(object_pointer, TD_GET_DIB_HANDLE, NULL, 0, 0);
   #define TD_GET_DIB_PALETTE           3
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TD_GET_DIB_PALETTE�� �о���� �׸����� �߿��� Palette������ ����� �ϴ� ��쿡 ���ȴ�. ��ȯ���� CPalette *���̴�.
// CPalette *p_palette = (CPalette *)GetDibOneProperty(object_pointer, TD_GET_DIB_PALETTE, NULL, 0, 0);
   #define TD_GET_DIB_PATH              4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TD_GET_DIB_PATH�� �о���� ������ ��θ��� �˷��ش�. ��ȯ�Ǵ� ���� char *���̴�.
// char *p_path = (char *)GetDibOneProperty(object_pointer, TD_GET_DIB_PATH, NULL, 0, 0);
   #define TD_IS_LOAD_DIB               5
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TD_IS_LOAD_DIB�� ������ ��Ʈ�� ��ü�� �о���� �̹��� ������ �ִ����� �˷��ش�. ��ȯ�Ǵ� ���� char ���̴�.
// char load_flag = (char)GetDibOneProperty(object_pointer, TD_IS_LOAD_DIB, NULL, 0, 0);
   #define TD_GET_DRAW_POSITION         6
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// +------------------------------------------------+
// |  Object Name :  TipsWare Normal Button Control |
// +------------------------------------------------+
//
// Microsoft Windows���� �����ϴ� �⺻���� Bitmap Button ��Ʈ���� Bitmap�� �̿��Ͽ� ��ư ��ü�� ǥ���ϴµ�
// ���� ������ ������ �ִ�. �׷��� ���� ���α׷��ӵ��� ����� ���� �׸���(Owner Drawing)����� ����� �̷� 
// ������ �غ��ϰ� �ִµ�, �� ��ü�� �׷��� ������ �����ϴ� ����� �����Ѵ�.
//
//   ���� ������ : �輺��.
//   ���� ������ : �輺��.              2000�� 4�� 3��
// ------------------------------------------------------
//        ������ : �輺��.              2000�� 4�� 7��
//          ���� : �Լ����� ���� �߰�.
// ------------------------------------------------------

// Tips Button ��Ʈ���� Subclassing ���� ���� �����Ͽ� ����ϰ��� �ϴ� ��쿡 ����ϴ� �Լ��̴�.
// 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. const char *parm_text
//    CButton ��Ʈ�ѿ� ����� ���ڿ��� �Է��Ѵ�. 
// 2. int parm_style
//    CButton ��Ʈ���� �Ӽ�(��/�� ����, ��/���� ����...)�� �����Ѵ�.
// 3. CRect parm_rect
//    ������ ��Ʈ���� ��ġ ��ǥ.
// 4. CWnd *parm_parent
//    ������ ��Ʈ���� ������ �������� ������.
// 5. int parm_id
//    ������ ��Ʈ���� ��Ʈ�� ID.
//
// �� �Լ��� CButton *�� ��ȯ�ϴµ�, �� ���� ���������� ������  Tips Button ��Ʈ�� ��ü�� �ּ��̴�. �� ��ü�� new �����ڸ�
// ����Ͽ� �������� �����Ǳ� ������ �Ѱ� ���� �ּҰ��� ������� ���Ҵٰ� �ݵ�� delete�ؾ� �Ѵ�. delete�ÿ��� Ư����
// �������̽��� ����� �ʿ���� ����ϰ� �ִ� �ش� �����͸� ���� delete��Ű�� �ȴ�. 
CButton *CreateTipsButtonObject(const char *, int , CRect , CWnd *, int );


// �Ϲ� Bitmap Button ��Ʈ���� Subclassing�Ͽ� Tips Button ��Ʈ���� �����ϴ� �Լ��̴�.
// 2���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. int parm_ctrl_id
//    Subclassing �� Bitmap Button ��Ʈ���� Resource ID.
// 2. CWnd *parm_parent
//    Subclassing �� Bitmap Button ��Ʈ���� �����ϴ� �������� ������.
//
// �� �Լ��� CButton *�� ��ȯ�ϴµ�, �� ���� ���������� ������ Tips Button ��Ʈ�� ��ü�� �ּ��̴�. �� ��ü�� new �����ڸ�
// ����Ͽ� �������� �����Ǳ� ������ �Ѱ� ���� �ּҰ��� ������ѳ��Ҵٰ� �ݵ�� delete�ؾ� �Ѵ�. delete�ÿ��� Ư����
// �������̽��� ����� �ʿ���� ����ϰ� �ִ� �ش� �����͸� ���� delete��Ű�� �ȴ�. 
CButton *CreateSubClassingTipsButtonObject(int , CWnd * );


// ������ Tips Button ��Ʈ�ѿ� �Ʒ��� ������ �Ӽ��� �����ϰ��� �ϴ� �Լ��̴�.
// �� 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1.CButton *parm_object
//    �Ӽ��� �����ϰ��� �ϴ� Tips Button ��Ʈ���� �ּ������̴�.
// 2. int parm_id
//    � �Ӽ��� ���������� ����. ���� ������ �Ӽ��� ������ �Լ� ������ ���� �Ŀ� ������ ����.
// 3. void *parm_property
//    �������� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 4. int parm_data1
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 5. int parm_data2
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
int SetTipsButtonOneProperty(CButton *, int , void *, int , int );
// SetTipsButtonOneProperty�Լ��� 2��° ������ parm_id�� ���� ���� 3~5�� ���޵Ǵ� ������ �����ȴ�. ���� ID�� ���� 
// �ʿ� ������ ��Ȯ���� ������ ������ �ʴ� ������ ��Ȳ�� �߻��Ҽ� �ִ�. ���� ������ �Ӽ��� �� 14�����̴�. �׸���
// ������ �ǹ̿� ������ ������ ����.
   #define TNB_SET_TEXT_REVISION            1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_SET_TEXT_REVISION�� Tips Button ��Ʈ���� �ؽ�Ʈ ���ڿ��� ��ġ�� ���� ����� �Ѵ�. 4��° �� 5��° ���ڸ� �̿��� ��
// �ְ� parm_data1�� ���� ���ڿ��� ��ġ�� X ��ǥ, parm_data2�� ���� ���ڿ��� ��ġ�� Y ��ǥ�� �����Ѵ�.
// SetTipsButtonOneProperty(object_pointer, TNB_SET_TEXT_REVISION, NULL, 7, 2);
   #define TNB_SET_IMAGE_REVISION           2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_SET_IMAGE_REVISION�� Tips Button ��Ʈ���� �̹��� ��ġ�� ���� ����� �Ѵ�. 4��° �� 5��° ���ڸ� �̿��� �� �ְ�
// parm_data1�� ���� �̹����� ��ġ�� X ��ǥ, parm_data2�� ���� ���ڿ��� ��ġ�� Y ��ǥ�� �����Ѵ�.
// SetTipsButtonOneProperty(object_pointer, TNB_SET_IMAGE_REVISION, NULL, 2, 2);
   #define TNB_SET_FONT                     3
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_SET_FONT�� Tips Button ��Ʈ�ѿ� �ܺο��� ������ ��Ʈ ��ü ������ ���� �����ϴ� ����� �Ѵ�. ���� ���������� �����ߴ�
// ��Ʈ ��ü ������ ���ŵǰ� ����ڰ� ������ ��Ʈ ��ü ������ ����Ѵ�. ��, �ܺο��� ���޵Ǵ� ��Ʈ ��ü�� ���Ӽ��� ������
// �־�߸� �Ѵ�. ���� ���, ���������� ����� ��Ʈ ��ü�� �ּҸ� �Ҵ��ϴ� ��� Tips Button ��Ʈ�ѿ� ������ �����. ���� 
// �ܺο��� �����Ǿ� ���޵Ǵ� ��Ʈ ��ü�� �ּ��� Tips Button ��Ʈ���� Life Time���ٴ� ���� �Ѵ�.
// CFont m_font;   <--  ��� ���� �Ǵ� ���� ����
// m_font.CreateFont.....
// SetTipsButtonOneProperty(object_pointer, TNB_SET_FONT, &m_font, 0, 0);
   #define TNB_CHANGE_FONT                  4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_CHANGE_FONT Tips Button  ��Ʈ�ѿ��� ����ϴ� ��Ʈ ��ü ������ �����Ѵ�. ����, ������ ������ ��Ʈ ��ü ������ �ִٸ� �����ϰ�
// �ܺο��� ������ ��Ʈ ��ü ������ �ִٸ� �ش� ������ ������� �ʵ��� ������ ������. �� ��쿡�� 3~5 ���ڰ� ��� ���Ǹ�
// ������ �ǹ̴� ������ ����.
// (3, parm_property) : ����ϰ��� �ϴ� ��Ʈ�� �̸�
// (4, parm_data1)    : ��Ʈ�� ������ �Ӽ��� ����� ���ΰ��� ����. (1�̸� ���, 0�Ƹ� ��� ����.)
// (5, parm_data2)    : ��Ʈ�� ũ�⸦ �����Ѵ�.  �⺻ ũ��� 12�� �����Ѵ�.
// ����ü�� ����ϰ� ũ�Ⱑ 12�̸� ���� �Ӽ��� ���� ��Ʈ�� ����ϰ� �ʹٸ� �Ʒ��� ���� �����ϸ� �ȴ�.
// SetTipsButtonOneProperty(object_pointer, TNB_CHANGE_FONT, "����ü", 1, 12);
   #define TNB_SET_BORDER_COLOR             5
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_SET_BORDER_COLOR�� Tips Button ��Ʈ���� ��Ŀ���� �����ϰ� �ִ¶��� ��Ŀ���� �Ҿ������� ��ư �ܺ��� ������ �����ϴ�
// ����� �Ѵ�. 4��° �� 5��° ���ڸ� �̿��� �� �ְ� parm_data1�� ���� ��Ŀ�� ���� ���� �϶��� ������ �����ϰ�, 
// parm_data2�� ���� ��Ŀ���� �Ҿ��� ���� ������ �����Ѵ�.
// SetTipsButtonOneProperty(object_pointer, TNB_SET_BORDER_COLOR, NULL, RGB(0,0,255), RGB(255,0,0));
   #define TNB_SET_TEXT_COLOR               6
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_SET_TEXT_COLOR Tips Button ��Ʈ���� �ؽ�Ʈ ���ڿ��� ������ �����ϴ� ����� �Ѵ�. 4��° �� 5��° ���ڸ� �̿��� ��
// �ְ� parm_data1�� ���� ��Ŀ�� ���� ���� �϶��� ������ �����ϰ�, parm_data2�� ���� ��Ŀ���� �Ҿ��� ���� ������ �����Ѵ�.
// SetTipsButtonOneProperty(object_pointer, TNB_SET_TEXT_COLOR, NULL, RGB(0,0,255), RGB(255,0,0));
   #define TNB_SET_WINDOW_TEXT              7
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_SET_WINDOW_TEXT Tips Button ��Ʈ�ѿ� ���Ե� �ý�Ʈ ������ �����ϴ� ����� �Ѵ�. 3��° ���ڿ� ���ϴ� ���ڿ��� �ּҸ� 
// �־��ָ� �ȴ�.
// CString my_string = "Hello My Control";
// SetTipsButtonOneProperty(object_pointer, TNB_SET_WINDOW_TEXT, (const char *)my_string, 0, 0);
//                               �Ǵ�
// SetTipsButtonOneProperty(object_pointer, TNB_SET_WINDOW_TEXT, "Hello My Control", 0, 0);
   #define TNB_SET_BITMAP                   8
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_SET_BITMAP�� Tips Button ��Ʈ�ѿ� ��Ʈ���� �ø��� ����� �Ѵ�. 3~5��° ���ڸ� �����ؾ��Ѵ�.
// parm_property�� ���� ��ư���� ��ġ�� bitmap�� ��� �� ȭ�ϸ��� �����ϰ�, parm_data1�� ���� ���� ����� ����� ��������
// �����ϴ� ��(1:���, 0:������)�̰� parm_data2�� parm_data1�� 1�� ��� ������ ������ �����Ѵ�.
// SetTipsButtonOneProperty(object_pointer, TNB_SET_BITMAP, ".\image\test.bmp", 0, RGB(192,192,192));
   #define TNB_SET_DEFAULT                  9
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_SET_DEFAULT�� Tips Button ��Ʈ���� Deafult �Ӽ��� �����ϴ� ����� �Ѵ�. 3��° �Ǵ� 4��° ���ڸ� �̿��� �� �ִ�.
// ���⼭ ���� �� ���� parm_property�� NULL�̸� parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property��
// ������ ������ �Լ��� �����Ѵ�. defaul�� ������ �Ǹ� ��Ŀ���� �Ҿ� ������ ��Ŀ�� ���� ������ ������ �����ϰ� �ȴ�.
// ������ �Ű������� char ������ ���� �Ͽ��� �Ѵ�.
// char m_set_dafault = 1;
// SetTipsButtonOneProperty(object_pointer, TNB_SET_DEFAULT,&m_set_dafault, 0);
//									�Ǵ�
// SetTipsButtonOneProperty(object_pointer, TNB_SET_DEFAULT,NULL, 1, 0);
   #define TNB_SET_FOCUS_MODE              10
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_SET_FOCUS_MODE Tips Button ��Ʈ���� focus ���¸� �����ϴ� ����� �Ѵ�. 3��° �Ǵ� 4��° ���ڸ� �̿��� �� �ִ�.
// ���⼭ ���� �� ���� parm_property�� NULL�̸� parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property��
// ������ ������ �Լ��� �����Ѵ�. ������ �Ű������� char ������ ���� �Ͽ��� �Ѵ�.
// char m_set_focus = 1;
// SetTipsButtonOneProperty(object_pointer, TNB_SET_FOCUS_MODE, &m_set_focus, 0, 0);
//									�Ǵ�
// SetTipsButtonOneProperty(object_pointer, TNB_SET_FOCUS_MODE, NULL, 1, 0);
   #define TNB_SET_TRANSPARENT_MODE        11
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_SET_TRANSPARENT_MODE�� Bitmap Button ��Ʈ���� ����� �����ϰ� ����� �������� �����Ѵ�. 3��° �Ǵ� 4��° ���ڸ�
// �̿��Ҽ� �ְ� �ش� ���� 1�̸� ����� �����ϰ� ����ϰ� 0�̸� ������ �������� ����Ѵ�. ���⼭ ���� �� ���� 
// parm_property�� NULL�̸� parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property�� ������ ������ 
// �Լ��� �����Ѵ�.
// char temp_flag = 1;
// SetTipsButtonOneProperty(object_pointer, TNB_SET_TRANSPARENT_MODE, &temp_flag, 0, 0);
//                               �Ǵ�
// SetTipsButtonOneProperty(object_pointer, TNB_SET_TRANSPARENT_MODE, NULL, 1, 0);
// Normal Bitmap Button ��Ʈ���� �⺻������ ����� �����ϰ� �ϴ� �Ӽ��� ������ �ֱ� ������ ó�� �����ɶ� ������ 
// ������ �����̴�. �׸��� 3��° ���ڸ� �̿��ϴ� ��� ����ϴ� ������ �ݵ�� char���̿��� �Ѵ�.
   #define TNB_SET_FILL_COLOR              12
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_SET_FILL_COLOR Bitmap Button ��Ʈ���� ������ �����ϴ� ����� �Ѵ�. 3��° �� 4��° ���ڸ� �̿��� �� �ְ� 
// parm_property�� NULL�̸� parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property�� ������ ������ 
// �Լ��� �����Ѵ�. ���⼭ ���� �ؾ� �� ���� ��ư�� �⺻ �Ӽ��� TRANSPARENT_MODE �� ���� �Ǿ� �����Ƿ� �ݵ�� 
// TRANSPARENT_MODE�� ������ �� ����ؾ� �Ѵ�.
// COLORREF m_color = RGB(0,0,255);
// SetTipsButtonOneProperty(object_pointer, TNB_SET_FILL_COLOR, &m_color, 0, 0);
//									�Ǵ�
// SetTipsButtonOneProperty(object_pointer, TNB_SET_FILL_COLOR, NULL, RGB(0,255,0), 0);
   #define TNB_RESET_BITMAP                13
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_RESET_BITMAP�� Tips Button ��Ʈ�ѿ� �ø� ��Ʈ���� ���� �ϴ� ����� �Ѵ�. 2��° �Ű��������� ���� �ϸ� �Ǹ�
// �ٸ� ���� ���� �ǹ̰� ����.
// SetTipsButtonOneProperty(object_pointer, TNB_RESET_BITMAP,NULL, 0, 0);
   #define TNB_UPDATE_OBJECT               14
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_UPDATE_OBJECT�� Tips Button ��Ʈ�ѿ� Ư�� �Ӽ��� �����ϴ� ����� ����. ���� ������ ������ �Ӽ����� ����� ��,
// ����� ������ ȭ������ ������ �Ҷ�, ��ü�� ������ ȭ���� ���Ž�Ű�� ����� ������ �ִ�. �׸��� ���ڴ� ������� �ʴ´�.
// SetTipsButtonOneProperty(object_pointer, TNB_UPDATE_OBJECT, NULL, 0, 0);


// ������ Tips Button ��Ʈ�ѿ� �Ʒ��� ������ �Ӽ��� � ���� �����Ǿ� �ִ��� �˰��� �ϴ� ��쿡 ����ϴ� �Լ��̴�.
// �� 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. CButton *parm_object
//    �Ӽ��� �˰��� �ϴ� Tips Button ��Ʈ���� ������.
// 2. int parm_id
//    � �Ӽ��� �˾Ƴ� �������� ����. ���� ������ �Ӽ��� ������ �Լ� ������ ���� �Ŀ� ������ ����.
// 3. void *parm_property
//    �������� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 4. int parm_data1
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 5. int parm_data2
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
int GetTipsButtonOneProperty(CButton *, int , void *, int , int );
// GetTipsButtonOneProperty�Լ��� 2��° ������ parm_id�� ���� ���� 3~5�� ���޵Ǵ� ������ �����ǰ� �ڽ��� ����� �ϴ� ������
// �����ȴ�. ���� ID�� �߸� �����ϰų� ID�� ���� �ʿ� ������ ��Ȯ���� ������ ������ �ʴ� ���� ������ ��ȯ�� ���� �ִ�.
// �� ��Ʈ�� ��ü�� �����ϴ� ������ �Ʒ��� ���� ��� 3���̸� ������ ������ ������ ����.
// ������ ���� �� �Լ��� �������� �뵵�� ����Ǿ��� ������ ��ɿ� ���� ������ ĳ����(Casting)�ؼ� ����ؾ� �Ѵ�.
   #define TNB_GET_DEFAULT                  1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_GET_DEFAULT�� Tips Button ��Ʈ���� Default ��ư���� �����Ǿ��ִ����� �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰� ������
// ��ȯ�Ǵ� ���� char ���̴�. ��ȯ���� 0�̸� Default�� �ƴ� �����̰� 1�̸� Default ���� �����̴�.
// char dibbutton_default_flag = (char)GetTipsButtonOneProperty(object_pointer, TNB_GET_DEFAULT, NULL, 0, 0);
   #define TNB_GET_FOCUS_MODE               2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_GET_FOCUS_MODE�� Tips Button ��Ʈ�� �� ��Ŀ���� ������ �ִ����� �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰� ������
// ��ȯ�Ǵ� ���� char ���̴�. ��ȯ���� 0�̸� ��Ŀ�� ������ �ʴ� �����̰� 1�̸� ��Ŀ���� ������ �ִ� �����̴�.
// char dibbutton_focus_flag = (char)GetTipsButtonOneProperty(object_pointer, TNB_GET_FOCUS_MODE, NULL, 0, 0);
   #define TNB_GET_TRANSPARENT_MODE         3
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_GET_TRANSPARENT_MODE�� Tips Button ��Ʈ���� ����� �����ϰ� �����Ǿ��ִ����� �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰�
// ������ ��ȯ�Ǵ� ���� char ���̴�. ��ȯ���� 0�̸� �������� ���� �����̰� 1�̸� ����� ������ �����̴�.
// char bitmapbutton_transparent_flag = (char)GetTipsButtonOneProperty(object_pointer, TNB_GET_TRANSPARENT_MODE, NULL, 0, 0);
   #define TNB_GET_WINDOW_TEXT              4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TNB_GET_WINDOW_TEXT�� Tips Button ��Ʈ�ѿ� ���Ե� �ý�Ʈ�� ������ �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰� ������ ��ȯ�Ǵ�
// ���� ���ڿ��� �����ּ��̴�. ��, const char * �Ǵ� char * ���̴�.
// const char *p_text = (const char *)GetTipsButtonOneProperty(object_pointer, TNB_GET_WINDOW_TEXT, NULL, 0, 0);

// +------------------------------------------------+
// |  Object Name :  Tips CheckButton Control             |
// +------------------------------------------------+
//
//  Microsoft Windows���� �����ϴ� �⺻���� Check Button ��Ʈ���� ����� ���� �׸���(Owner Drawing)����� �̿��� Check Button��
//  �ܼ��� ǥ�� ����� ���� �ϵ��� �Ѵ�.
//
//   ���� ������ : �輺�� ����.
//   ���� ������ : �輺�� ����.    2000�� 3�� 28��
// ------------------------------------------------
//        ������ :                     ��  ��   ��
//        ���� : 
// ------------------------------------------------

// Check Button ��Ʈ���� Subclassing ���� ���� �����Ͽ� ����ϰ��� �ϴ� ��쿡 ����ϴ� �Լ��̴�.
// 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. const char *parm_text
//    Static ��Ʈ�ѿ� ����� ���ڿ��� �Է��Ѵ�. 
// 2. int parm_style
//    Static ��Ʈ���� �Ӽ�(��/�� ����, ��/���� ����...)�� �����Ѵ�.
// 3. CRect parm_rect
//    ������ ��Ʈ���� ��ġ ��ǥ.
// 4. CWnd *parm_parent
//    ������ ��Ʈ���� ������ �������� ������.
// 5. int parm_id
//    ������ ��Ʈ���� ��Ʈ�� ID.
//
// �� �Լ��� CButton *�� ��ȯ�ϴµ�, �� ���� ���������� ������ Check Button ��Ʈ�� ��ü�� �ּ��̴�. �� ��ü�� new �����ڸ�
// ����Ͽ� �������� �����Ǳ� ������ �Ѱ� ���� �ּҰ��� ������� ���Ҵٰ� �ݵ�� delete�ؾ� �Ѵ�. delete�ÿ��� Ư����
// �������̽��� ����� �ʿ� ���� ����ϰ� �ִ� �ش� �����͸� ���� delete��Ű�� �ȴ�. 
CButton *CreateCheckButtonObject(const char *, int , CRect , CWnd *, int );


// �Ϲ� Check Button ��Ʈ���� Subclassing�Ͽ� Check Button ��Ʈ���� �����ϴ� �Լ��̴�.
// 2���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. int parm_ctrl_id
//    Subclassing �� Check Button ��Ʈ���� Resource ID.
// 2. CWnd *parm_parent
//    Subclassing �� Check Button ��Ʈ���� �����ϴ� �������� ������.
//
// �� �Լ��� CButton *�� ��ȯ�ϴµ�, �� ���� ���������� ������ Check Button ��Ʈ�� ��ü�� �ּ��̴�. �� ��ü�� new �����ڸ�
// ����Ͽ� �������� �����Ǳ� ������ �Ѱ� ���� �ּҰ��� ������ѳ��Ҵٰ� �ݵ�� delete�ؾ� �Ѵ�. delete�ÿ��� Ư���� 
// �������̽��� ����� �ʿ���� ����ϰ� �ִ� �ش� �����͸� ���� delete��Ű�� �ȴ�. 
CButton *CreateSubClassingCheckButtonObject(int , CWnd *);


// ������ Check Button ��Ʈ�ѿ� �Ʒ��� ������ �Ӽ��� �����ϰ��� �ϴ� �Լ��̴�.
// �� 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1.CButton *parm_object
//    �Ӽ��� �����ϰ��� �ϴ� Check Button ��Ʈ���� �ּ������̴�.
// 2. int parm_id
//    � �Ӽ��� ���������� ����. ���� ������ �Ӽ��� ������ �Լ� ������ ���� �Ŀ� ������ ����.
// 3. void *parm_property
//    �������� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 4. int parm_data1
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 5. int parm_data2
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
int SetCheckButtonOneProperty(CButton *, int , void *, int , int );
// SetCheckButtonOneProperty�Լ��� 2��° ������ parm_id�� ���� ���� 3~5�� ���޵Ǵ� ������ �����ȴ�. ���� ID�� ���� 
// �ʿ� ������ ��Ȯ���� ������ ������ �ʴ� ������ ��Ȳ�� �߻��Ҽ� �ִ�. ���� ������ �Ӽ��� �� 9�����̴�. �׸���
// ������ �ǹ̿� ������ ������ ����.
   #define TC_SET_COLOR                 1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_SET_COLOR�� CheckButton ��Ʈ���� ��Ŀ���� ������ �ִ°�? �ƴѰ�? �� ���� ���Ե� �ؽ�Ʈ ������ �����ϴ� ����� �Ѵ�.
// RGB ������ 4��°�� 5��° ���ڿ� ���ϴ� ���� �־��ָ� �ȴ�.
//	SetCheckButtonOneProperty(object_pointer, TC_SET_COLOR, NULL, RGB(0, 0, 0), RGB(255,255,255));
   #define TC_SET_FONT                  2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_SET_FONT�� CheckButton ��Ʈ�ѿ� �ܺο��� ������ ��Ʈ ��ü ������ ���� �����ϴ� ����� �Ѵ�. ���� ���������� �����ߴ�
// ��Ʈ ��ü ������ ���ŵǰ� ����ڰ� ������ ��Ʈ ��ü ������ ����Ѵ�. ��, �ܺο��� ���޵Ǵ� ��Ʈ ��ü�� ���Ӽ��� ������
// �־�߸� �Ѵ�. ���� ���, ���������� ����� ��Ʈ ��ü�� �ּҸ� �Ҵ��ϴ� ��� CheckButton ��Ʈ�ѿ� ������ �����. ���� 
// �ܺο��� �����Ǿ� ���޵Ǵ� ��Ʈ ��ü�� �ּ��� CheckButton ��Ʈ���� Life Time���ٴ� ���� �Ѵ�.
// CFont m_font;   <--  ��� ���� �Ǵ� ���� ����
// m_font.CreateFont.....
// SetCheckButtonOneProperty(object_pointer,  TC_SET_FONT, &m_font, 0, 0);
   #define TC_CHANGE_FONT               3
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_CHANGE_FONT�� CheckButton ��Ʈ�ѿ��� ����ϴ� ��Ʈ ��ü ������ �����Ѵ�. ����, ������ ������ ��Ʈ ��ü ������ �ִٸ�
// �����ϰ� �ܺο��� ������ ��Ʈ ��ü ������ �ִٸ� �ش� ������ ������� �ʵ��� ������ ������.
// �� ��쿡�� 3~5 ���ڰ� ��� ���Ǹ� ������ �ǹ̴� ������ ����.
// (3, parm_property) : ����ϰ��� �ϴ� ��Ʈ�� �̸�
// (4, parm_data1)    : ��Ʈ�� ������ �Ӽ��� ����� ���ΰ��� ����. (1�̸� ���, 0�Ƹ� ��� ����.)
// (5, parm_data2)    : ��Ʈ�� ũ�⸦ �����Ѵ�.  �⺻ ũ��� 12�� �����Ѵ�.
// ����ü�� ����ϰ� ũ�Ⱑ 12�̸� ���� �Ӽ��� ���� ��Ʈ�� ����ϰ� �ʹٸ� �Ʒ��� ���� �����ϸ� �ȴ�.
// SetCheckButtonOneProperty(object_pointer, TC_CHANGE_FONT, "����ü", 1, 12);
   #define TC_SET_WINDOW_TEXT           4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_SET_WINDOW_TEXT�� CheckButton ��Ʈ�ѿ� ���Ե� �ý�Ʈ ������ �����ϴ� ����� �Ѵ�. 3��° ���ڿ� ���ϴ� ���ڿ��� �ּҸ� 
// �־��ָ� �ȴ�.
// CString my_string = "Hello My Control";
// SetCheckButtonOneProperty(object_pointer, TC_SET_WINDOW_TEXT, (const char *)my_string, 0, 0);
//                               �Ǵ�
// SetCheckButtonOneProperty(object_pointer, TC_SET_WINDOW_TEXT, "Hello My Control", 0, 0);
   #define TC_SET_TRANSPARENT_MODE      5
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_SET_TRANSPARENT_MODE�� CheckButton ��Ʈ���� ����� �����ϰ� ����� �������� �����Ѵ�. 3��° �Ǵ� 4��° ���ڸ� �̿���
// �� �ְ� �ش� ���� 1�̸� ����� �����ϰ� ����ϰ� 0�̸� ������ �������� ����Ѵ�. ���⼭ ���� �� ���� parm_property��
// NULL�̸� parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property�� ������ ������ �Լ��� �����Ѵ�.
// char temp_flag = 1;
// SetCheckButtonOneProperty(object_pointer, TC_SET_TRANSPARENT_MODE, &temp_flag, 0, 0);
//                               �Ǵ�
// SetCheckButtonOneProperty(object_pointer, TC_SET_TRANSPARENT_MODE, NULL, 1, 0);
// CheckButton ��Ʈ���� �⺻������ ����� �����ϰ� �ϴ� �Ӽ��� ������ �ֱ� ������ ó�� �����ɶ� ������ ������ �����̴�.
// �׸��� 3��° ���ڸ� �̿��ϴ� ��� ����ϴ� ������ �ݵ�� char���̿��� �Ѵ�.
   #define TC_SET_BK_COLOR              6
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_SET_BK_COLOR�� CheckButton ��Ʈ�ѿ� ������ �����ϴ� ����� �Ѵ�. 3��° �Ǵ� 4��° ���ڸ� �̿��� �� �ְ� 
// parm_property�� NULL�̸� parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property�� ������ ������ �Լ���
// �����Ѵ�. ���� �� �Ӽ��� ����� �������� �ʴٰ� ������ ��쿡�� �Ӽ��� ��ȿ�ϴ�.
// COLORREF temp_color = RGB(0, 0, 255);
// SetCheckButtonOneProperty(object_pointer, TC_SET_BK_COLOR, &temp_color, 0, 0);
//                               �Ǵ�
// SetCheckButtonOneProperty(object_pointer, TC_SET_BK_COLOR, NULL, RGB(0, 0, 255), 0);
   #define TC_SET_FIX_POS               7
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_SET_FIX_POS�� Check Button ��Ʈ���� �⺻ ��ġ�� ���� �ϴ� ����� �Ѵ�. 3��° �Ǵ� 4��° ���ڸ� �̿��� �� �ְ� 
// parm_property�� NULL�̸� parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property�� ������ ������ �Լ���
// �����Ѵ�. 
// int checkbutton_pos = 20;
// SetCheckButtonOneProperty(object_pointer, TC_SET_FIX_POS, &checkbutton_pos, 0, 0);
//                               �Ǵ�
// SetCheckButtonOneProperty(object_pointer, TC_SET_FIX_POS, NULL, 20, 0);
   #define TC_SET_IMAGE_PATH            8
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_SET_IMAGE_PATH�� Check Button ��Ʈ���� ��Ÿ���� bitmap�� �����ϴ� ����� �Ѵ�. 3��° �Ǵ� 4��° ���ڸ� �̿��Ͽ� 
// bitmap�� �����Ѵ�. parm_property�� bitmap�� ��ġ�̰�, parm_data1�� Check Button �� bitmap�� ��� �ִ� �迭�� ��ġ�̴�.
// SetCheckButtonOneProperty(object_pointer, TC_SET_IMAGE_PATH, ".\MMCC_IMAGE", 1, 0);
   #define TC_UPDATE_OBJECT             9
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_UPDATE_OBJECT�� CheckButton ��Ʈ�ѿ� Ư�� �Ӽ��� �����ϴ� ����� ����. ���� ������ ������ �Ӽ����� ����� ��,
// ����� ������ ȭ������ ������ �Ҷ�, ��ü�� ������ ȭ���� ���Ž�Ű�� ����� ������ �ִ�. �׸��� ���ڴ� ������� �ʴ´�.
// SetCheckButtonOneProperty(object_pointer, TC_UPDATE_OBJECT, NULL, 0, 0);


// ������ Normal CheckButton ��Ʈ�ѿ� �Ʒ��� ������ �Ӽ��� � ���� �����Ǿ� �ִ��� �˰��� �ϴ� ��쿡 ����ϴ� �Լ��̴�.
// �� 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. CButton *parm_object
//    �Ӽ��� �˰��� �ϴ� Normal CheckButton ��Ʈ���� ������.
// 2. int parm_id
//    � �Ӽ��� �˾Ƴ� �������� ����. ���� ������ �Ӽ��� ������ �Լ� ������ ���� �Ŀ� ������ ����.
// 3. void *parm_property
//    �������� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 4. int parm_data1
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 5. int parm_data2
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
int GetCheckButtonOneProperty(CButton *, int , void *, int , int );
// GetCheckButtonOneProperty�Լ��� 2��° ������ parm_id�� ���� ���� 3~5�� ���޵Ǵ� ������ �����ǰ� �ڽ��� ����� �ϴ� ������
// �����ȴ�. ���� ID�� �߸� �����ϰų� ID�� ���� �ʿ� ������ ��Ȯ���� ������ ������ �ʴ� ���� ������ ��ȯ�� ���� �ִ�.
// �� ��Ʈ�� ��ü�� �����ϴ� ������ �Ʒ��� ���� ��� 4���̸� ������ ������ ������ ����.
// ������ ���� �� �Լ��� �������� �뵵�� ����Ǿ��� ������ ��ɿ� ���� ������ ĳ����(Casting)�ؼ� ����ؾ� �Ѵ�.
   #define TC_GET_WINDOW_TEXT           1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_GET_WINDOW_TEXT�� CheckButton ��Ʈ�ѿ� ���Ե� �ý�Ʈ�� ������ �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰� ������ ��ȯ�Ǵ� ����
// ���ڿ��� �����ּ��̴�. ��, const char * �Ǵ� char * ���̴�.
// const char *p_text = (const char *)GetCheckButtonOneProperty(object_pointer, TC_GET_WINDOW_TEXT, NULL, 0, 0);
   #define TC_GET_TRANSPARENT_MODE      2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_GET_TRANSPARENT_MODE�� CheckButton ��Ʈ���� ����� �����ϰ� �����Ǿ��ִ����� �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰� ������
// ��ȯ�Ǵ� ���� char ���̴�. ��ȯ���� 0�̸� �������� ���� �����̰� 1�̸� ����� ������ �����̴�.
// char checkbutton_transparent_flag = (char)GetCheckButtonOneProperty(object_pointer, TC_GET_TRANSPARENT_MODE, NULL, 0, 0);
   #define TC_GET_BK_COLOR              3
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_GET_BK_COLOR�� CheckButton ��Ʈ�ѿ� ���Ե� �ý�Ʈ�� ��� ������ �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰� ������ ��ȯ�Ǵ� ����
// COLORREF���̴�. �׸��� �� ���� ������ �������� �ʴٰ� ����� ��쿡�� ��ȿ�ϴ�.
// COLORREF checkbutton_color = (COLORREF)GetCheckButtonOneProperty(object_pointer, TC_GET_BK_COLOR, NULL, 0, 0);
   #define TC_GET_FIX_POS               4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TC_GET_FIX_POS�� CheckButton ��Ʈ���� �⺻ ��ġ�� �˾Ƴ��� ����� �Ѵ�. ���ڵ��� �ǹ̰� ������
// ��ȯ�Ǵ� ���� int ���̴�. ��ȯ����ŭ CheckButton ��Ʈ���� �⺻ ��ġ�� ��Ÿ����.
// int checkbutton_pos = GetCheckButtonOneProperty(object_pointer, TC_GET_FIX_POS, NULL, 0, 0);

// +------------------------------------------------+
// |  Object Name :  Tips ListBox Control        |
// +------------------------------------------------+
//
//  Microsoft Windows���� �����ϴ� �⺻���� ListBox ��Ʈ���� �ڽ��� ������ �ִ� �����͸� ǥ���ϴµ� ���� ������ ������ �ִ�.
//  �׷��� ���� ���α׷��ӵ��� ����� ���� �׸���(Owner Drawing)����� ����� �̷� ������ �غ��ϰ� �ִµ�, �� ��ü��
//  �׷��� ������ �����ϰ� ���� ���� ������� ������ ����� �����Ѵ�.
//
//   ���� ������ : �輺�� ����.
//   ���� ������ : �輺�� ����.    2000�� 3�� 17��
// ------------------------------------------------
//        ������ :                     ��  ��   ��
//          ���� : 
// ------------------------------------------------

// ���Լ��� ����ڰ� ������ ��ġ, ID, style�� ListBox ��ü�� �����Ѵ�. �� �Լ��� 8���� ���ڸ� ������ �� ������ ������ ����.
// 1. CWnd *parm_parent
//    ListBox ��ü�� ������ �������� �ּ� ����. ���� ���� �����Ǵ� ListBox ��ü�� parm_parent �������� �ڽ� �����찡 �ȴ�.
// 2. int parm_control_id
//    ������ ListBox ��Ʈ���� ID�� �Է��Ѵ�. ListBox Ŭ������ �ڽ��� ���º�ȭ�� ������� ���ۿ� ���� Notify �޽����� �ڽ���
//    �θ� �����쿡�� �����Ѵ�. �̶�, �θ� ������� �� ID�� ������ � ��ü���� �ش� �޽����� �Դ����� �����Ѵ�.
// 3. int parm_x
//    ������ ListBox ��Ʈ���� x�� �������� �����Ѵ�.
// 4. int parm_y
//    ������ ListBox ��Ʈ���� y�� �������� �����Ѵ�.
// 5. int parm_cx
//    ������ ListBox ��Ʈ���� x�� ũ�⸦ �����Ѵ�.
// 6. int parm_cy
//    ������ ListBox ��Ʈ���� y�� ũ�⸦ �����Ѵ�.
// 7. int parm_type
//    ������ ListBox ��Ʈ���� ���� ������ �Ӽ������� �����Ѵ�. �⺻������ ����ϴ� �Ӽ��� ������ ����.
//    7.1  Single Selection & Single Column.
//		   WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_OWNERDRAWFIXED | WS_CLIPSIBLINGS | LBS_NOTIFY |
//		   LBS_SORT | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT);
//    7.2  Single Selection & Multi Column.
//	       WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | LBS_OWNERDRAWFIXED | WS_CLIPSIBLINGS | LBS_NOTIFY |
//		   LBS_SORT | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT | LBS_MULTICOLUMN);
//    7.3  Multi Selection & Single Column.
//         WS_CHILD | WS_BORDER | WS_HSCROLL | LBS_OWNERDRAWFIXED | WS_CLIPSIBLINGS | LBS_NOTIFY | LBS_EXTENDEDSEL |   
//		   LBS_SORT | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT);
//    7.4  Multi Selection & Multi Column.
//         WS_CHILD | WS_BORDER | WS_HSCROLL | LBS_OWNERDRAWFIXED | WS_CLIPSIBLINGS | LBS_NOTIFY | LBS_EXTENDEDSEL |   
//		   LBS_SORT | LBS_MULTICOLUMN | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT);
// 8. int parm_ext_type
//     ����Ʈ �ڽ��� Extened Window style�� �����Ѵ�..
//
// �� �Լ��� CListBox *�� ��ȯ�ϴµ�, �� ���� ���������� ������ ListBox ��Ʈ�� ��ü�� �ּ��̴�. �� ��ü�� new �����ڸ�
// ����Ͽ� �������� �����Ǳ� ������ �Ѱ� ���� �ּҰ��� ������ѳ��Ҵٰ� �ݵ�� delete�ؾ� �Ѵ�. delete�ÿ��� Ư����
// �������̽��� ����� �ʿ���� ����ϰ� �ִ� �ش� �����͸� ���� delete��Ű�� �ȴ�. 
CListBox *CreateListBox(CWnd *, int , int , int , int , int , int, int );


// ������ ListBox ��Ʈ�ѿ� �Ʒ��� ������ �Ӽ��� �����ϰ��� �ϴ� �Լ��̴�.
// �� 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. CListBox *parm_object
//    �Ӽ��� �����ϰ��� �ϴ� ListBox ��Ʈ���� �ּ������̴�.
// 2. int parm_id
//    � �Ӽ��� ���������� ����. ���� ������ �Ӽ��� ������ �Լ� ������ ���� �Ŀ� ������ ����.
// 3. void *parm_property
//    �������� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 4. int parm_data1
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 5. int parm_data2
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
int SetListBoxOneProperty(CListBox *, int , void *, int , int );
// SetListBoxOneProperty�Լ��� 2��° ������ parm_id�� ���� ���� 3~5�� ���޵Ǵ� ������ �����ȴ�. ���� ID�� ���� 
// �ʿ� ������ ��Ȯ���� ������ ������ �ʴ� ������ ��Ȳ�� �߻��Ҽ� �ִ�. ���� ������ �Ӽ��� �� 5�����̴�. �׸���
// ������ �ǹ̿� ������ ������ ����.
   #define TL_SET_WIDTH                 1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TL_SET_WIDTH�� ������ ListBox�� ��(width)�� ũ�⸦ �����ϴ� ����� �Ѵ�. 3��°�� 4��° ���ڿ� ���ϴ� ���� �־��ָ� �ȴ�.
// ���⼭ ���� �� ���� parm_property�� NULL�̸� parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property��
// ������ ������ �Լ��� �����Ѵ�.
// int list_width = 240;
// SetListBoxOneProperty(object_pointer, TL_SET_WIDTH, &list_width, 0, 0);
//                               �Ǵ�
// SetListBoxOneProperty(object_pointer, TL_SET_WIDTH, NULL, 240, 0);
   #define TL_SET_HEIGHT                2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TL_SET_HEIGHT�� ������ ListBox�� ����(height)�� ũ�⸦ �����ϴ� ����� �Ѵ�. 3��°�� 4��° ���ڿ� ���ϴ� ���� �־��ָ� �ȴ�.
// ���⼭ ���� �� ���� parm_property�� NULL�̸� parm_data1�� ���� ��ȿ�ϰ� parm_property�� NULL�� �ƴϸ� parm_property��
// ������ ������ �Լ��� �����Ѵ�.
// int list_height = 150;
// SetListBoxOneProperty(object_pointer, TL_SET_HEIGHT, &list_height, 0, 0);
//                               �Ǵ�
// SetListBoxOneProperty(object_pointer, TL_SET_HEIGHT, NULL, 150, 0);
   #define TL_SET_BACKGROUND_COLOR      3
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TL_SET_BACKGROUND_COLOR�� ������ ListBox�� ���� �� ���� ���� �����ϴ� ����� �Ѵ�. 4��°�� 5��° ���ڿ� ���ϴ� ������ �־��ָ� �ȴ�.
// SetListBoxOneProperty(object_pointer, TL_SET_BACKGROUND_COLOR, NULL, RGB(0, 0, 255), RGB(0, 0, 255));
   #define TL_SET_CURSOR                4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TL_SET_CURSOR�� ������ ListBox�� Item�� ���õǾ����� ǥ�õǴ� Ŀ���� ������ �����ϴ� ����� �Ѵ�. 4~5�� ���� ���� �־��ָ�
// �ǰ� ������ �ǹ̴� ������ ����.
// (4, parm_data1)    : Ŀ���� ä��� ����. ( Brush ���� ���� )
// (5, parm_data2)    : Ŀ���� �׵θ� ���� ����. ( Pen ���� ���� )
// SetListBoxOneProperty(object_pointer, TL_SET_CURSOR, NULL, RGB(255, 251, 240), RGB(192, 192, 192));
   #define TL_SET_DISPLAY_FUNCTION      5
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TL_SET_DISPLAY_FUNCTION�� ������ ListBox ��ü�� ������ �ִ� ������ ������� ������ ���ΰ��� ������ �Լ��� ���� 
// �������̴�. ListBox ��ü���� ���� ���� �ٲ�� �κ��� �� ��ü�� �����ϰ� �ִ� ������ ���� ǥ������̴�. ���� �̷���
// ǥ������� ���� ���Ǵ� ��ü �ܺο��� �ڵ��Ǿ� �������̽� �Լ��� ���Ͽ� ��ü�� ���η� ���޵Ǿ� ���Ǿ� ����.
// �ܺο��� ���ǵǾ����� �Լ� �Ʒ��� ���� ���·� ���ǵǾ����� �ϸ� �̰��� �ݵ�� ������������ �Ѵ�.
// ---------------------------------------------------------------------------------------------------------------------------
// void display_function(CWnd *parm_base_wnd, CListBox *parm_this, int parm_index, CRect parm_rect, HDC parm_dc, char parm_push_flag);
// �� �Լ��� ���޵Ǵ� ������ �Ű������� ���ؼ� �����ϸ� ������ ����.
// -. CWnd *parm_base_wnd
//    ListBox ��Ʈ�� ��ü�� ������ �θ� �������� ������..
// -. CListBox *parm_list
//    �� ListBox ��Ʈ�� ��ü�� ����ϴ� ���� �Ƹ� CWnd Ŭ���� �迭�� Ŭ�����߿� �ϳ��� ���̴�. ���� �� ��ü�� �ش� Ŭ������
//    ������ ����� ����� ���̰� ����Լ��� �ƴϸ� �� ��ü�� ������ �˾Ƴ��� ����. ������ display_function�� � Ư��
//    Ŭ������ �ҼӵǾ ������� �ʱ� ������ �ڽ��� �̿��ϰ� �� ListBox ��ü�� ���ؼ� �ƹ��� ������ ������ ���� �ʴ�.
//    ���� display_function�� ����� ListBox ��Ʈ�� ��ü�� �� �Լ��� ȣ���Ҷ�. ù���� ������ parm_list�� �ڽ��� this ����
//    ������ �ش�. ���� ����ڴ� �� �ּ��������� �ڽ��� ���ϴ� ������ ���� �ڵ带 �ϼ��ϸ� �ȴ�.
// -. int parm_index
//    ListBox�� ���� �׸��� ���� ����ؾ��� �׸��� index ��. ListBox�� ���� ����� ��ü���� �ϰ� ������ �ƴ϶�, �׸� ������
//    �ϱ� ������ �ݵ�� parm_index ���� �̿��ؼ� �ش�Ǵ� �������� �����ؾ� �Ѵ�.
// -. CRect parm_rect
//    ListBox�� ���� �׸��� ���� ����ؾ��� �׸��� ��ġ �����̴�. �ٸ� �׸��� ������ ħ������ �ʵ��� �� ���� ������ �
//    ������ ��Ÿ����� �Ѵ�.
// -. HDC parm_dc
//    ����ϰ� �ִ� ListBox�� �Ҵ��� DC�����̴�. ���ο� DC�� �����ؼ� ������ ������� ���� �ݵ�� �� DC�� �̿��ؼ� �����
//    �ؾ����� ��Ȯ�� ��� ����� ������ �ִ�.
// -. char parm_push_flag
//    �� �׸��� ���õ� ���, ���õ��� ���� ����� �ΰ����� ���¸� ������. �� ���� �� ���¸� ���������ش�. �� ���� 0�̸�
//    ���� ����ؾ� �� �׸��� ������ ���� ���� ����̰� 1�̸� ���õ� ����̴�.
// ---------------------------------------------------------------------------------------------------------------------------
// �ܺο��� ������ �Լ��� �ּҰ��� SetListBoxOneProperty�� 3��° ������ ���޵Ǿ�����.
// SetListBoxOneProperty(object_pointer, TL_SET_DISPLAY_FUNCTION, display_function, 0, 0);


// ������ ListBox ��Ʈ�ѿ� �Ʒ��� ������ �Ӽ��� � ���� �����Ǿ� �ִ��� �˰��� �ϴ� ��쿡 ����ϴ� �Լ��̴�.
// �� 5���� ���ڸ� ������ �� ������ ������ ������ ������ ����.
// 1. CListBox *parm_object
//    �Ӽ��� �˰��� �ϴ� ListBox ��Ʈ���� ������.
// 2. int parm_id
//    � �Ӽ��� �˾Ƴ� �������� ����. ���� ������ �Ӽ��� ������ �Լ� ������ ���� �Ŀ� ������ ����.
// 3. void *parm_property
//    �������� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 4. int parm_data1
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
// 5. int parm_data2
//    ����� ���� ������ ���� ���� �����Ѵ�.  ( parm_id�� ���� ���� �������� �ǹ̴� �޶�����. )
int GetListBoxOneProperty(CListBox *, int , void *, int , int );
// GetListBoxOneProperty 2��° ������ parm_id�� ���� ���� 3~5�� ���޵Ǵ� ������ �����ǰ� �ڽ��� ����� �ϴ� ������
// �����ȴ�. ���� ID�� �߸� �����ϰų� ID�� ���� �ʿ� ������ ��Ȯ���� ������ ������ �ʴ� ���� ������ ��ȯ�� ���� �ִ�.
// �� ��Ʈ�� ��ü�� �����ϴ� ������ �Ʒ��� ���� ��� 2���̸� ������ ������ ������ ����.
// ������ ���� �� �Լ��� �������� �뵵�� ����Ǿ��� ������ ��ɿ� ���� ������ ĳ����(Casting)�ؼ� ����ؾ� �Ѵ�.
   #define TL_GET_WIDTH                 1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TL_GET_WIDTH�� ������ ListBox ��ü�� ��(width)�� ũ�⸦ �˰��� �ϴ� ��쿡 ���ȴ�. Ư���� �Ű������� ������� ������
// ��ȯ�Ǵ� ���� int ���̴�.
// int list_width = (int)GetDibOneProperty(object_pointer, TL_GET_WIDTH, NULL, 0, 0);
   #define TL_GET_HEIGHT                2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TL_GET_HEIGHT�� ������ ListBox ��ü�� ����(height)�� ũ�⸦ �˰��� �ϴ� ��쿡 ���ȴ�. Ư���� �Ű������� ������� ������
// ��ȯ�Ǵ� ���� int ���̴�.
// int list_height = (int)GetDibOneProperty(object_pointer, TL_GET_HEIGHT, NULL, 0, 0);


CButton *CreateTipsMenuButtonObject(const char *parm_text, int parm_style, CRect parm_rect, CWnd *parm_parent, int parm_id);
CButton *CreateSubClassingTipsMenuButtonObject(int parm_ctrl_id, CWnd *parm_parent);


#define TMB_SET_TEXT_REVISION            1
#define TMB_SET_IMAGE_REVISION           2
#define TMB_SET_FONT                     3
#define TMB_CHANGE_FONT                  4
#define TMB_SET_BORDER_COLOR             5
#define TMB_SET_TEXT_COLOR               6
#define TMB_SET_WINDOW_TEXT              7
#define TMB_SET_BITMAP                   8
#define TMB_SET_DEFAULT                  9
#define TMB_SET_FOCUS_MODE              10
#define TMB_SET_TRANSPARENT_MODE        11
#define TMB_SET_FILL_COLOR              12
#define TMB_RESET_BITMAP                13
#define TMB_UPDATE_OBJECT               14

int SetTipsMenuButtonOneProperty(CButton *parm_object, int parm_id, void *parm_property, int parm_data1, int parm_data2);

#define TMB_GET_DEFAULT                  1
#define TMB_GET_FOCUS_MODE               2
#define TMB_GET_TRANSPARENT_MODE         3
#define TMB_GET_WINDOW_TEXT              4

int GetTipsMenuButtonOneProperty(CButton *parm_object, int parm_id, void *parm_property, int parm_data1, int parm_data2);


CComboBox *CreateComboBox(CWnd *parm_parent, int parm_control_id, int parm_x, int parm_y, int parm_cx, int parm_cy, int parm_type, int parm_ext_type);

#define TCB_SET_HEIGHT                1
#define TCB_SET_BACKGROUND_COLOR      2
#define TCB_SET_CURSOR                3
#define TCB_SET_DISPLAY_FUNCTION      4
int SetComboBoxOneProperty(CComboBox *parm_object, int parm_id, void *parm_property, int parm_data1, int parm_data2);

#define TCB_GET_HEIGHT                1
int GetComboBoxOneProperty(CComboBox *parm_object, int parm_id, void *parm_property, int parm_data1, int parm_data2);

CListBox *CreateDriveListBox(CWnd *parm_parent, int parm_control_id, int parm_x, int parm_y, int parm_cx, int parm_cy, int parm_type, int parm_ext_type);

#define TDL_SET_BACKGROUND_COLOR      1
#define TDL_SET_SELECTED_COLOR        2
#define TDL_SET_CURSOR                3
int SetDriveListBoxOneProperty(CListBox *parm_object, int parm_id, void *parm_property, int parm_data1, int parm_data2);

void ShowMentBox(HWND parm_parent, int parm_wait_time, char parm_on_top, const char *parm_title, const char *parm_content, int parm_wdith);


extern void TAPI_LoadSystemButtonImage();
extern void TAPI_DeleteSystemButtonImage();
extern void TAPI_ShowDibButtonImage(CDC *pDC, int parm_x, int parm_y, char parm_index);

class TipsDIB;

class StandardWnd : public CWnd
{
private:
	TipsDIB *mp_bk_image[9];

	CFont m_font;
	char m_is_clicked, m_is_active_state;
	CPoint m_original_pos, m_clicked_pos, m_original_size;

protected:
	CString m_caption_main, m_caption_sub;
	char m_is_maximized, m_resize_flag;
	char m_max_flag, m_min_flag, m_close_flag;
	int m_limit_x_size, m_limit_y_size;

// Construction
public:
	StandardWnd();
	virtual ~StandardWnd();

	void SetWindowTextExt(const char *parm_main, const char *parm_sub);
	void DisplayActiveState(CDC *parm_dc, CRect parm_rect);
	void SetWindowSystemMenu(char parm_min, char parm_max, char parm_close);
	virtual void OnViewDraw(CDC *pDC);
	
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	DECLARE_MESSAGE_MAP()
};

class StandardDialog : public CDialog
{
private:
	TipsDIB *mp_bk_image[9];

	CFont m_font;
	char m_is_clicked, m_is_active_state;
	CPoint m_original_pos, m_move_pos, m_clicked_pos, m_original_size;

protected:
	CString m_caption_main, m_caption_sub;
	char m_is_maximized, m_resize_flag;
	char m_max_flag, m_min_flag, m_close_flag;
	int m_limit_x_size, m_limit_y_size;

// Construction
public:
	StandardDialog(unsigned int parm_id, CWnd* pParent = NULL);

	void SetWindowTextExt(const char *parm_main, const char *parm_sub);
	void DisplayActiveState(CDC *parm_dc, CRect parm_rect);
	void SetWindowSystemMenu(char parm_min, char parm_max, char parm_close);
	virtual void OnViewDraw(CDC *pDC);

	enum { IDD = 0 };

protected:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	DECLARE_MESSAGE_MAP()
};

struct node {				//  ����Ʈ�� �����ϰ� �� ����� ����..
	void *p_object;			//  ����� ���� ��ü�� �����ϱ� ���� ����ϴ� ������..
	node *p_next;			//  ���� ��带 ����Ű�� ������..
};

class TipsWareList
{				  
private : 
	node *mp_head,*mp_tail;	 // ����Ʈ�� ó���� ���� ����Ű�� ������..
	int m_node_count;		 // ����� ������ ������ �ִ� ����..

public :
	TipsWareList();           // ��ü ������..
	virtual ~TipsWareList();  // ��ü �ı���..

	void InitListObject();
	char AddObject(void *parm_object,int parm_size);    // ���ο� ��带 �߰��ϴ� ���, (����)
	char AddObject(void *parm_object);			        // ���ο� ��带 �߰��ϴ� ���, (����)
	char AddObjectByIndex(int parm_index, void *parm_object);
	char DeleteObject(node *parm_node);	                // �����ϴ� ��带 �����ϴ� ���..
	char DeleteNodeExceptObject(node *parm_object);
	char DeleteHeadObject();							// ���� ó�� ��带 �����ϴ� ���..
	void DeleteAllObject();								// �����ϴ� ��ü ��θ� �����ϴ� ���..
	void DeleteAllObjectExceptObject();			        // �����ϴ� ��带 ��� �����Ѵ�..
	char DeleteObjectByIndex(int parm_index);			// ����ڰ� ������ ��ġ�� �����ϴ� ��ü�� �ı��Ѵ�.
	char DeleteNodeExceptObjectByIndex(int parm_index);

	node *GetNodeByIndex(int parm_index);
	void *GetObjectByIndex(int parm_index);
	int FindNodeIndexByObject(void *parm_object);

	node *GetHeadObject(); 								// ���� ù ����� �ּҸ� ��´�..
	node *GetTailObject(); 								// ���� ������ ����� �ּҸ� ��´�..
	int GetNodeCount();									// ����� ������ ��´�..
};

#define MAX_TOKEN_LEN    120
#define MAX_COMMAND      5

class StandardWndExt;

typedef struct InternalWindowObject {
	int type;
	char *p_name;
	CWnd *p_wnd;
} IWO;

typedef struct CommandType {
	char c_name[MAX_TOKEN_LEN];      
	void (StandardWndExt::*p)();
} CT;

class StandardWndExt : public StandardWnd
{
private:
	char m_token[MAX_TOKEN_LEN];      // m_token string
	char m_token_type;                // m_token type
	char m_tok_id;                       
	char *mp_buff, *mp_script_data;
	CT m_command[MAX_COMMAND];
	CString m_file_path;

protected:
	TipsWareList m_object_list;

// Construction
public:
	StandardWndExt();
	virtual ~StandardWndExt();

	void OnViewDraw(CDC *pDC);

	int GetTokenData();
	int LookUpCommand(char *s);
	int IsDelimiter(char c);
	int IsWhiteSpace(char c);
	void SyntaxErrorInScript();
	void SetScript(char *parm_script);
	const char *GetCurrentFilePath();
	void InitObject();
	void DeleteObject();
	void RunScript();

	IWO *GetControlByName(const char *parm_name);
	void GetRectData(int parm_rect[], char parm_remove_prev_comma);
	const char *GetStringData(char parm_remove_prev_comma);
	int GetIntData(char parm_remove_prev_comma);

	void CreateTipsButton();
	void CreateTipsStatic();
	void CreateTipsCheck();
	void CreateTipsDIB();
	void CreateTipsListBox();

protected:
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
};

class StandardDialogExt : public StandardDialog
{
private:
	char m_token[MAX_TOKEN_LEN];      // m_token string
	char m_token_type;                // m_token type
	char m_tok_id;                       
	char *mp_buff, *mp_script_data;
	CT m_command[MAX_COMMAND];
	CString m_file_path;

protected:
	TipsWareList m_object_list;

// Construction
public:
	StandardDialogExt(unsigned int parm_id, CWnd* pParent = NULL);
	
	virtual void OnViewDraw(CDC *pDC);

	int GetTokenData();
	int LookUpCommand(char *s);
	int IsDelimiter(char c);
	int IsWhiteSpace(char c);
	void SyntaxErrorInScript();
	void SetScript(char *parm_script);
	const char *GetCurrentFilePath();
	void InitObject();
	void DeleteObject();
	void RunScript();

	IWO *GetControlByName(const char *parm_name);
	void GetRectData(int parm_rect[], char parm_remove_prev_comma);
	const char *GetStringData(char parm_remove_prev_comma);
	int GetIntData(char parm_remove_prev_comma);

	void CreateTipsButton();
	void CreateTipsStatic();
	void CreateTipsCheck();
	void CreateTipsDIB();
	void CreateTipsListBox();

	enum { IDD = 0 };

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
};

class TipsProcThread : public CWinThread
{
private:
	CWnd *mp_control_wnd;
	HANDLE mh_kill_event;
	int m_exit_notify_id;

// Attributes
public:
	TipsProcThread(CWnd *parm_control_wnd, UINT (*parm_fp)(LPVOID), void *parm_data, int parm_exit_notify_id);
	virtual ~TipsProcThread();

	void StartThread(int parm_level);
	void KillProcThread();
	HANDLE GetKillEventHandle();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

#endif
