#pragma once

//=================================
// ObjectPool<T,MAX>クラス
//
//  ゲームループ内の動的メモリ確保を避けるための固定長オブジェクトプール
//  T型のオブジェクトをMAX個、起動時にまとめて確保
//  実行中はalloc()とfree()で管理
//
//=================================
template<typename T,int MAX>
class ObjectPool{
public:
    //実オブジェクト領域
    T pool[MAX];

private:
    //フリーリスト(未使用オブジェクトのインデックス使用)
    //  alloc()で末尾から取得、free()で末尾へ戻す
    int freeList[MAX];
    int freeCount;  //freeLitの有効要素数

    //アクティブリスト(使用中オブジェクトのインデックス管理)
    // activeList:
    //  使用中(pool上)オブジェクトの一覧
    //
    // activeIndex:
    //  pool[i]がactiveListの何番目か
    //  「O(1)での削除」の実現のために使用
    int activeList[MAX];
    int activeIndex[MAX];   //pool Index -> activeLsit上の位置の上書き
    int activeCount;        //activeListの有効要素数

public:
    //コンストラクタ:全要素をフリーリストに登録
    ObjectPool(){
        freeCount = MAX;
        activeCount = 0;

        for(int i=0;i<MAX;i++){
            //最初は全要素が未使用なので、freeListに詰める
            freeList[i] = i;

            activeList[i] = 0;
            activeIndex[i] = 0;
        }
    }

    //生成(オブジェクト取得)
    //  未使用要素を1つ確保して返す
    T* alloc(){
        //空きがない場合はnullptrを返す
        if(freeCount == 0)return nullptr;

        //未使用領域を1つ取得
        int index = freeList[--freeCount];

        //使用中リストへ追加(逆引きインデックスも更新)
        activeList[activeCount] = index;
        activeIndex[index] = activeCount;
        activeCount++;

        //返されたオブジェクトは呼び出し側で初期化
        return &pool[index];
    }

    //解放(オブジェクト返却)
    //  使用中の要素を返却、再利用できるように
    //  @param obj alloc()で取得したポインタ(nullptrならなにもしない)
    void free(T* obj){
        if(!obj)return;

        //pool配列上のインデックスへ変換
        int index = obj - pool;

        //未使用リストへ返却
        freeList[freeCount++] = index;

        //activeListから削除(O(1))
        //  1.削除対象のactiveList上の位置を逆引きで取得
        //  2.activeListの末尾要素を削除位置に上書き
        //  3.activeCountを1減らす
        //      ->末尾と入れ替え、配列の詰め替えが不要に
        int pos = activeIndex[index];
        int last = activeList[--activeCount];

        if(last != index){
            //末尾要素を削除位置に移動、逆引きも更新
            activeList[pos] = last;
            activeIndex[last] = pos;
        }
    }

    //使用中要素全体に対して、funcを呼び出す(初期化などに使用)
    //非アクティブな要素は走査しない
    template<typename Func>
    void forEachActive(Func func){
        for(int i=0;i<activeCount;i++){
            func(pool[activeList[i]]);
        }
    }

    //デバック用:メモリ使用率の可視化に使用
    int getActiveCount() const {return activeCount;}
    int getCapacity() const {return MAX;}
    float getUsageRate() const {
        return static_cast<float>(activeCount)/static_cast<float>(MAX);
    }
};