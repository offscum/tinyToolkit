#ifndef __POOL__OBJECT_POOL__H__
#define __POOL__OBJECT_POOL__H__


/**
 *
 * 作者: hm
 *
 * 说明: 对象池
 *
 */


#include "../common/define.h"
#include "../common/symbol.h"
#include "../common/version.h"

#include <cstring>
#include <unordered_set>


namespace tinyToolkit
{
	namespace pool
	{
		template <typename ObjectType, std::size_t CHUNK_SIZE = 4>
		class ObjectPool
		{
			struct ChunkList;

			struct Chunk
			{
				char buffer[sizeof(ObjectType)]{ 0 };

				Chunk * prev{ nullptr };
				Chunk * next{ nullptr };
			};

			struct ChunkList
			{
				Chunk chunks[CHUNK_SIZE]{ };

				ChunkList * prev{ nullptr };
				ChunkList * next{ nullptr };
			};

		public:
			/**
			 *
			 * 析构函数
			 *
			 */
			~ObjectPool()
			{
				Close();
			}

		public:
			/**
			 *
			 * 关闭
			 *
			 */
			void Close()
			{
				for (auto & lend : _lends)
				{
					reinterpret_cast<ObjectType *>(lend)->~ObjectType();
				}

				_lends.clear();

				while (_chunkListHead)
				{
					DeleteChunkList(_chunkListHead);
				}
			}

			/**
			 *
			 * 归还
			 *
			 * @param object 对象
			 *
			 * @return 是否归还成功
			 *
			 */
			bool Return(ObjectType * object)
			{
				if (object == nullptr)
				{
					return false;
				}

				auto chunk = reinterpret_cast<Chunk *>(object);

				auto find = _lends.find(chunk);

				if (find == _lends.end())
				{
					return false;
				}

				_lends.erase(find);

				ReturnChunk(chunk);

				return true;
			}

			/**
			 *
			 * 借出
			 *
			 * @param args 参数
			 *
			 * @return 对象
			 *
			 */
			template <typename... Args>
			ObjectType * Lend(Args &&... args)
			{
				auto * chunk = LendChunk();

				if (chunk == nullptr)
				{
					return nullptr;
				}

				_lends.insert(chunk);

				return new(chunk->buffer) ObjectType(std::forward<Args>(args)...);
			}

			/**
			 *
			 * 个数
			 *
			 * @return 个数
			 *
			 */
			std::size_t Count() const
			{
				return _count;
			}

			/**
			 *
			 * 借出个数
			 *
			 * @return 借出个数
			 *
			 */
			std::size_t LendCount() const
			{
				return _lends.size();
			}

		private:
			/**
			 *
			 * 提交数据块
			 *
			 * @param chunk 数据块
			 *
			 */
			void PushChunk(Chunk * chunk)
			{
				if (chunk == nullptr)
				{
					return;
				}

				::memset(chunk->buffer, 0, sizeof(ObjectType));

				chunk->next = _chunkHead;

				if (_chunkHead)
				{
					_chunkHead->prev = chunk;
				}

				_chunkHead = chunk;
			}

			/**
			 *
			 * 断开数据块
			 *
			 * @param chunk 数据块
			 *
			 */
			void BrokenChunk(Chunk * chunk)
			{
				if (chunk == nullptr)
				{
					return;
				}

				if (chunk->prev)
				{
					chunk->prev->next = chunk->next;
				}

				if (chunk->next)
				{
					chunk->next->prev = chunk->prev;
				}

				if (chunk == _chunkHead)
				{
					_chunkHead = chunk->next;
				}

				chunk->prev = nullptr;
				chunk->next = nullptr;
			}

			/**
			 *
			 * 归还数据块
			 *
			 * @param chunk 数据块
			 *
			 */
			void ReturnChunk(Chunk * chunk)
			{
				if (chunk == nullptr)
				{
					return;
				}

				reinterpret_cast<ObjectType *>(chunk)->~ObjectType();

				PushChunk(chunk);
			}

			/**
			 *
			 * 提交数据块链表
			 *
			 * @param chunkList 数据块链表
			 *
			 */
			void PushChunkList(ChunkList * chunkList)
			{
				if (chunkList == nullptr)
				{
					return;
				}

				for (std::size_t i = 0; i < CHUNK_SIZE; ++i)
				{
					chunkList->chunks[i].prev = nullptr;
					chunkList->chunks[i].next = nullptr;

					PushChunk(&(chunkList->chunks[i]));
				}

				chunkList->prev = nullptr;
				chunkList->next = _chunkListHead;

				if (_chunkListHead)
				{
					_chunkListHead->prev = chunkList;
				}

				_chunkListHead = chunkList;

				_count += CHUNK_SIZE;
			}

			/**
			 *
			 * 删除数据块链表
			 *
			 * @param chunkList 数据块链表
			 *
			 */
			void DeleteChunkList(ChunkList * chunkList)
			{
				if (chunkList == nullptr)
				{
					return;
				}

				for (std::size_t i = 0; i < CHUNK_SIZE; ++i)
				{
					BrokenChunk(&(chunkList->chunks[i]));
				}

				if (chunkList->prev)
				{
					chunkList->prev->next = chunkList->next;
				}

				if (chunkList->next)
				{
					chunkList->next->prev = chunkList->prev;
				}

				if (chunkList == _chunkListHead)
				{
					_chunkListHead = chunkList->next;
				}

				delete chunkList;

				_count -= CHUNK_SIZE;
			}

			/**
			 *
			 * 借出数据块
			 *
			 * @return 数据块
			 *
			 */
			Chunk * LendChunk()
			{
				if (_chunkHead == nullptr)
				{
					PushChunkList(new ChunkList);
				}

				auto chunk = _chunkHead;

				BrokenChunk(chunk);

				return chunk;
			}

		private:
			Chunk * _chunkHead{ nullptr };

			ChunkList * _chunkListHead{ nullptr };

			std::size_t _count{ 0 };

			std::unordered_set<Chunk *> _lends{ };
		};
	}
}


#endif // __POOL__OBJECT_POOL__H__
