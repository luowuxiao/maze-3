#ifndef __FILE_UTILS_H_
#define __FILE_UTILS_H_

#include <functional>

/** һ��һ�еĶ��ļ� , ÿ�ζ�һ��wchar
@param [in] path ·��
@param [in] checker �ļ�ͷУ��
@param [in] checkSize checker�Ĵ�С
@param [in] callback �ص�
@return �Ƿ�ɹ�
*/
bool HandleFileByLineW(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::wstring&line)> callback);

/** һ��һ�еĶ��ļ� UCS-2 Little Endian ����
@param [in] path ·��
@param [in] callback �ص�
@return �Ƿ�ɹ�
*/
bool HandleUCS2FileByLine(const std::wstring& path, std::function<bool(const std::wstring&line)> callback);

/** д�ļ�
@param [in] path ·��
@param [in] header �ļ�ͷУ��
@param [in] headSize header�Ĵ�С
@param [in] callback �ص����� ���ؼ���Ҫд���ļ������ݣ�size ����Ҫд���ļ��Ĵ�С����ע�ⵥ˫�ֽڣ�˫�ֽڱ����˳�2,hasNext��ʶ�Ƿ�����һ��
@return �Ƿ�ɹ�
*/
bool WriteFileByBuff(const std::wstring& path, const unsigned char* header, const size_t headSize, std::function<const void* (size_t& size, bool& hasNext)> callback);

/** д�ļ� UCS-2 Little Endian ����
@param [in] path ·��
@param [in] callback �ص����� ���ؼ���Ҫд���ļ������ݣ� size ����Ҫд���ļ��Ĵ�С����ע�ⵥ˫�ֽڣ�˫�ֽڱ����˳�2,hasNext��ʶ�Ƿ�����һ��
@return �Ƿ�ɹ�
*/
bool WriteUCS2FileByBuff(const std::wstring& path, std::function<const void* (size_t& size, bool& hasNext)> callback);

#endif //__FILE_UTILS_H_
