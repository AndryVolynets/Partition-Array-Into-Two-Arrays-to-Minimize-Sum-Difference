# Partition-Array-Into-Two-Arrays-to-Minimize-Sum-Difference

# 2035. Partition Array Into Two Arrays to Minimize Sum Difference
<p>Return <em>the <strong>minimum</strong> possible absolute difference</em>.</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="example-1" src="https://assets.leetcode.com/uploads/2021/10/02/ex1.png" style="width: 240px; height: 106px;">
<pre><strong>Input:</strong> nums = [3,9,7,3]
<strong>Output:</strong> 2
<strong>Explanation:</strong> One optimal partition is: [3,9] and [7,3].
The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.
</pre>
<p><strong class="example">Example 2:</strong></p>
<pre><strong>Input:</strong> nums = [-36,36]
<strong>Output:</strong> 72
<strong>Explanation:</strong> One optimal partition is: [-36] and [36].
The absolute difference between the sums of the arrays is abs((-36) - (36)) = 72.
</pre>
<p><strong class="example">Example 3:</strong></p>
<img alt="example-3" src="https://assets.leetcode.com/uploads/2021/10/02/ex3.png" style="width: 316px; height: 106px;">
<pre><strong>Input:</strong> nums = [2,-1,0,4,-2,-9]
<strong>Output:</strong> 0
<strong>Explanation:</strong> One optimal partition is: [2,4,-9] and [-1,0,-2].
The absolute difference between the sums of the arrays is abs((2 + 4 + -9) - (-1 + 0 + -2)) = 0.
</pre>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= n &lt;= 15</code></li>
	<li><code>nums.length == 2 * n</code></li>
	<li><code>-10<sup>7</sup> &lt;= nums[i] &lt;= 10<sup>7</sup></code></li>
</ul>
</div></div>
<p><strong>My solution:</strong></p>

<pre>
<div class="bg-black rounded-md mb-4">
<div class="flex items-center relative text-gray-200 bg-gray-800 px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span></span><button class="flex ml-auto gap-2"><svg stroke="currentColor" fill="none" stroke-width="2" viewBox="0 0 24 24" stroke-linecap="round" stroke-linejoin="round" class="h-4 w-4" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"></path><rect x="8" y="2" width="8" height="4" rx="1" ry="1"></rect></svg</button></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-c++"><span class="hljs-meta">#<span class="hljs-keyword">include</span> <span class="hljs-string">&lt;vector&gt;</span></span>
<span class="hljs-meta">#<span class="hljs-keyword">include</span> <span class="hljs-string">&lt;algorithm&gt;</span></span>
<span class="hljs-keyword">using</span> <span class="hljs-keyword">namespace</span> std;

<span class="hljs-keyword">class</span> <span class="hljs-title class_">Solution</span> {
<span class="hljs-keyword">public</span>:
    <span class="hljs-function"><span class="hljs-type">int</span> <span class="hljs-title">minimumDifference</span><span class="hljs-params">(vector&lt;<span class="hljs-type">int</span>&gt;&amp; nums)</span> </span>{
        <span class="hljs-type">const</span> <span class="hljs-type">int</span> half_size = nums.<span class="hljs-built_in">size</span>() / <span class="hljs-number">2</span>;
        <span class="hljs-type">const</span> <span class="hljs-type">int</span> quarter_size = nums.<span class="hljs-built_in">size</span>() / <span class="hljs-number">4</span>;

        vector&lt;vector&lt;<span class="hljs-type">int</span>&gt;&gt; <span class="hljs-built_in">s1</span>(quarter_size + <span class="hljs-number">1</span>);
        vector&lt;vector&lt;<span class="hljs-type">int</span>&gt;&gt; <span class="hljs-built_in">s2</span>(quarter_size + <span class="hljs-number">1</span>);

        <span class="hljs-built_in">dfs</span>(nums, <span class="hljs-number">0</span>, half_size, <span class="hljs-number">0</span>, <span class="hljs-number">0</span>, s1);
        <span class="hljs-built_in">dfs</span>(nums, half_size, nums.<span class="hljs-built_in">size</span>(), <span class="hljs-number">0</span>, <span class="hljs-number">0</span>, s2);

        <span class="hljs-keyword">return</span> <span class="hljs-built_in">countDiff</span>(
            s1,
            s2,
            quarter_size,
            <span class="hljs-built_in">accumulate</span>(nums.<span class="hljs-built_in">begin</span>(), nums.<span class="hljs-built_in">begin</span>() + half_size, <span class="hljs-number">0</span>),
            <span class="hljs-built_in">accumulate</span>(nums.<span class="hljs-built_in">begin</span>() + half_size, nums.<span class="hljs-built_in">end</span>(), <span class="hljs-number">0</span>)
        );
    }

    <span class="hljs-function"><span class="hljs-type">int</span> <span class="hljs-title">countDiff</span><span class="hljs-params">(<span class="hljs-type">const</span> vector&lt;vector&lt;<span class="hljs-type">int</span>&gt;&gt;&amp; s1, <span class="hljs-type">const</span> vector&lt;vector&lt;<span class="hljs-type">int</span>&gt;&gt;&amp; s2, <span class="hljs-type">int</span> quarter_size, <span class="hljs-type">const</span> <span class="hljs-type">int</span> sum1, <span class="hljs-type">const</span> <span class="hljs-type">int</span> sum2)</span> <span class="hljs-type">const</span>
    </span>{
        <span class="hljs-type">int</span> min_diff = <span class="hljs-number">0x7fffffff</span>;

        <span class="hljs-keyword">for</span> (<span class="hljs-type">int</span> k = <span class="hljs-number">0</span>; k &lt;= quarter_size; ++k)
        {
            vector&lt;<span class="hljs-type">int</span>&gt; s2_sorted = s2[k];
            <span class="hljs-built_in">sort</span>(s2_sorted.<span class="hljs-built_in">begin</span>(), s2_sorted.<span class="hljs-built_in">end</span>());

            <span class="hljs-keyword">for</span> (<span class="hljs-type">int</span> s1_sum : s1[k])
            {
                <span class="hljs-type">int</span> conn = (sum1 + sum2) / <span class="hljs-number">2</span> - (sum1 - s1_sum);

                <span class="hljs-keyword">auto</span> it = <span class="hljs-built_in">lower_bound</span>(s2_sorted.<span class="hljs-built_in">begin</span>(), s2_sorted.<span class="hljs-built_in">end</span>(), conn);

                <span class="hljs-type">int</span> diff = (sum1 - sum2 - <span class="hljs-number">2</span> * s1_sum);
                <span class="hljs-type">int</span> absolute_diff = <span class="hljs-built_in">getMinDiff</span>(s2_sorted, diff, it);

                min_diff = <span class="hljs-built_in">min</span>(min_diff, absolute_diff);
            }
        }

        <span class="hljs-keyword">return</span> min_diff;
    }

    <span class="hljs-function"><span class="hljs-type">int</span> <span class="hljs-title">getMinDiff</span><span class="hljs-params">(<span class="hljs-type">const</span> vector&lt;<span class="hljs-type">int</span>&gt;&amp; s2_k, <span class="hljs-type">int</span> diff, vector&lt;<span class="hljs-type">int</span>&gt;::const_iterator it_value)</span> <span class="hljs-type">const</span>
    </span>{
        <span class="hljs-type">int</span> min_diff = <span class="hljs-number">0x7fffffff</span>;

        <span class="hljs-keyword">if</span> (!(it_value != s2_k.<span class="hljs-built_in">end</span>() || it_value != s2_k.<span class="hljs-built_in">begin</span>())) {
            <span class="hljs-keyword">return</span> min_diff;
        }
        <span class="hljs-keyword">else</span>
        {
            <span class="hljs-keyword">if</span> (it_value != s2_k.<span class="hljs-built_in">end</span>()) {
                min_diff = <span class="hljs-built_in">min</span>(min_diff, <span class="hljs-built_in">abs</span>(diff + (*it_value) * <span class="hljs-number">2</span>));
            }
            <span class="hljs-keyword">if</span> (it_value != s2_k.<span class="hljs-built_in">begin</span>()) {
                min_diff = <span class="hljs-built_in">min</span>(min_diff, <span class="hljs-built_in">abs</span>(diff + (*(--it_value)) * <span class="hljs-number">2</span>));
            }
            <span class="hljs-keyword">return</span> min_diff;
        }
    }


    <span class="hljs-function"><span class="hljs-type">void</span> <span class="hljs-title">dfs</span><span class="hljs-params">(<span class="hljs-type">const</span> vector&lt;<span class="hljs-type">int</span>&gt;&amp; nums, <span class="hljs-type">int</span> i, <span class="hljs-type">int</span> end, <span class="hljs-type">int</span> k, <span class="hljs-type">int</span> sum, vector&lt;vector&lt;<span class="hljs-type">int</span>&gt;&gt;&amp; sums)</span> <span class="hljs-type">const</span> </span>{
        <span class="hljs-keyword">if</span> (i != end &amp;&amp; k &lt; nums.<span class="hljs-built_in">size</span>() / <span class="hljs-number">4</span>) {
            <span class="hljs-built_in">dfs</span>(nums, i + <span class="hljs-number">1</span>, end, k, sum, sums);
            <span class="hljs-built_in">dfs</span>(nums, i + <span class="hljs-number">1</span>, end, k + <span class="hljs-number">1</span>, sum + nums[i], sums);
        }
        <span class="hljs-keyword">else</span> {
            sums[k].<span class="hljs-built_in">push_back</span>(sum);
        }
    }
};
</code></div></div></pre>

